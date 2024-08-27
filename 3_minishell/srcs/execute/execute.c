/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:47:22 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/27 20:56:02 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 명령어가 1개 일때,
void	execute_single(t_process *proc, char ***envp)
{
	int			dup_fd[2];
	pid_t		pid;

	dup_fd[0] = dup(0);
	dup_fd[1] = dup(1);
	ft_redirect(proc->redirs);
	if (ck_is_builtin(proc))
		exec_builtin(proc, envp);
	else
	{
		pid = fork();
		if (pid == -1)
			handle_error(2);
		else if (pid == 0)
			ft_execve(proc, *envp);
		else
			wait(NULL);
	}
	dup2(dup_fd[0], 0);
	dup2(dup_fd[1], 1);
}

// (명령어가 여러 개 일 때,) 자식 프로세스의 일
void	execute_child(t_process *proc, int (*pipe_fd)[2], int *rem_fd, char ***envp)
{
	if (proc->next)
		dup2((*pipe_fd)[1], 1);
	close((*pipe_fd)[1]);
	if (*rem_fd != -1)
	{
		dup2(*rem_fd, 0);
		close(*rem_fd);
	}
	close((*pipe_fd)[0]);
	ft_redirect(proc->redirs);
	if (ck_is_builtin(proc))
	{
		exec_builtin(proc, envp);
		exit(0);
	}
	else
		ft_execve(proc, *envp);
}

// 명령어가 여러 개 일 때,
void	execute_multiple(t_process *proc, char ***envp)
{
	int			pipe_fd[2];
	int			rem_fd;
	pid_t		pid;

	rem_fd = -1;
	while (proc)
	{
		pipe(pipe_fd); // 오류 처리 해줘야 할 듯
		pid = fork();
		if (pid == -1)
			handle_error(2);
		else if (pid == 0)
			execute_child(proc, &pipe_fd, &rem_fd, envp);
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
}

void	execute(t_envi	*envi, char ***envp)
{
	t_process	*proc;
	int			proc_num;
	int			idx;

	proc = envi->procs;
	proc_num = proc_len(proc);
	if (proc_num == 1)
		execute_single(proc, envp);
	else
	{
		execute_multiple(proc, envp);
		idx = 0;
		while (idx++ < proc_num)
			wait(NULL);
	}
}
