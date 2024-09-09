/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:47:22 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/09 21:59:32 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single(t_process *proc, char ***envp, int (*dup_fd)[3])
{
	int			stat;
	pid_t		pid;

	stat = ft_redirect_one(proc->redirs, proc->files, *envp, (*dup_fd)[0]);
	if (stat || !(proc->files))
		return (dup2_all(dup_fd, stat));
	if (ck_is_builtin(proc))
		stat = exec_builtin(proc, envp);
	else
	{
		pid = fork();
		if (pid == -1)
			handle_error(0);
		else if (pid == 0)
		{
			reset_sig_termi();
			ft_execve(proc, *envp);
		}
		else
			stat = get_exitcode(pid, 1);
	}
	return (dup2_all(dup_fd, stat));
}

void	execute_child(t_process *proc, int (*pipe_fd)[2],
						int *rem_fd, char ***envp, int std_in)
{
	int	stat;

	stat = 0;
	if (proc->next)
		dup2((*pipe_fd)[1], 1);
	close((*pipe_fd)[1]);
	if (*rem_fd != -1)
	{
		dup2(*rem_fd, 0);
		close(*rem_fd);
	}
	close((*pipe_fd)[0]);
	ft_redirect(proc->redirs, proc->files, *envp, std_in);
	if (g_sig)
		exit(g_sig);
	if (!(proc->files))
		exit(0);
	if (ck_is_builtin(proc))
	{
		stat = exec_builtin(proc, envp);
		exit(stat);
	}
	else
		ft_execve(proc, *envp);
}

void	execute_parent(int (*pipe_fd)[2], int *rem_fd, t_process *proc)
{
	close((*pipe_fd)[1]);
	if (*rem_fd != -1)
		close(*rem_fd);
	if (proc->next)
		*rem_fd = (*pipe_fd)[0];
	else
		close((*pipe_fd)[0]);
}

int	execute_multiple(t_process *proc, char ***envp,
					int proc_num, int (*dup_fd)[3])
{
	int			pipe_fd[2];
	int			rem_fd;
	int			stat;
	pid_t		pid;

	rem_fd = -1;
	stat = 0;
	while (proc && g_sig == 0)
	{
		if (pipe(pipe_fd) != 0)
			return (1);
		pid = fork();
		if (pid == -1)
			handle_error(0);
		else if (pid == 0)
		{
			reset_sig_termi();
			execute_child(proc, &pipe_fd, &rem_fd, envp, *dup_fd[0]);
		}
		else
			execute_parent(&pipe_fd, &rem_fd, proc);
		proc = proc->next;
	}
	stat = get_exitcode(pid, proc_num);
	return (stat);
}

void	execute(t_envi	*envi, char ***envp)
{
	t_process	*proc;
	int			proc_num;
	int			stat;
	int			dup_fd[3];

	proc = envi->procs;
	proc_num = proc_len(proc);
	stat = 0;
	dup_all(&dup_fd);
	init_sig();
	if (proc_num == 0
		|| (proc_num == 1 && proc->files && ft_strlen(proc->files->data) == 0))
		stat = send_errmsg_in("", " : command not found\n", 127);
	else if (proc_num == 1)
		stat = execute_single(proc, envp, &dup_fd);
	else
		stat = execute_multiple(proc, envp, proc_num, &dup_fd);
	record_exitcode(stat, envp);
	if (access(".heredoctmp", F_OK) == 0)
	{
		unlink(".heredoctmp");
		free_envi(envi);
		return ;
	}
	free_envi(envi);
}
