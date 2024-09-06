/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:47:22 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/06 17:52:54 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 명령어가 1개 일때,
int	execute_single(t_process *proc, char ***envp)
{
	int			dup_fd[2];
	int			stat;
	pid_t		pid;

	dup_fd[0] = dup(0);
	dup_fd[1] = dup(1);
	ft_redirect(proc->redirs, proc->files, *envp);
	stat = 0;
	if (ck_is_builtin(proc))
		stat = exec_builtin(proc, envp);
	else
	{
		pid = fork();
		if (pid == -1)
			handle_error(0);
		else if (pid == 0)
		{
			restore_signal();
			ft_execve(proc, *envp);
		}
		else
			stat = get_exitcode(pid, 1);
	}
	dup2(dup_fd[0], 0);
	dup2(dup_fd[1], 1);
	return (stat);
}

// (명령어가 여러 개 일 때,) 자식 프로세스의 일
void	execute_child(t_process *proc, int (*pipe_fd)[2], int *rem_fd, char ***envp)
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
	ft_redirect(proc->redirs, proc->files, *envp);
	if (ck_is_builtin(proc))
	{
		stat = exec_builtin(proc, envp);
		exit(stat);
	}
	else
		ft_execve(proc, *envp);
}

// 명령어가 여러 개 일 때,
int	execute_multiple(t_process *proc, char ***envp, int proc_num)
{
	int			pipe_fd[2];
	int			rem_fd;
	int			stat;
	pid_t		pid;

	rem_fd = -1;
	stat = 0;
	while (proc)
	{
		if (pipe(pipe_fd) != 0)
			return (1);
		pid = fork();
		if (pid == -1)
			handle_error(0);
		else if (pid == 0)
		{
			restore_signal();
			execute_child(proc, &pipe_fd, &rem_fd, envp);
		}
		else
		{
			close(pipe_fd[1]);
			if (rem_fd != -1)
				close(rem_fd);
			if (proc->next)
				rem_fd = pipe_fd[0];
			else
				close(pipe_fd[0]);
		}
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

	proc = envi->procs;
	proc_num = proc_len(proc);
	stat = 0;
	if (proc_num == 1)
		stat = execute_single(proc, envp);
	else
		stat = execute_multiple(proc, envp, proc_num);
	record_exitcode(stat, envp);
	if (access(".heredoctmp", F_OK) == 0)
		unlink(".heredoctmp");
}
