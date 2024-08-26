/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:47:22 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/26 13:30:44 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exc_builtin(t_process *proc, char ***envp)
{
	char	*cmd;
	t_file	*file;

	cmd = proc->files->data;
	file = proc->files->next;
	if (ft_strncmp("echo", cmd, 5) == 0)
		ft_echo(file);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		ft_pwd();
	else if (ft_strncmp("cd", cmd, 3) == 0)
		ft_cd(file);
	else if (ft_strncmp("export", cmd, 7) == 0)
		ft_export(file, envp);
	else if (ft_strncmp("env", cmd, 4) == 0)
		ft_env(*envp);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		ft_unset(envp, file);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		ft_exit(file);
	else
		return ;
}

int ck_is_builtin(t_process *proc)
{
	char	*cmd;

	cmd = proc->files->data;
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (2);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		return (3);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (4);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (5);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (6);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (7);
	else
		return (0);
}

// PATH를 가진 str을 만듦
char	*mk_path(char **envp)
{
	char	*path;
	int		mark;
	int		idx;
	int		idx2;

	mark = 0;
	while (envp[mark]) // PATH가 없는 경우도 생각해야하나?
	{
		if (ft_strncmp("PATH=", envp[mark], 5) == 0)
			break ;
		mark++;
	}
	path = (char *)malloc(sizeof(char) * ((int)ft_strlen(envp[mark]) - 4));
	if (!path)
		return (0); // error 나중에 생각 해서 바꾸기
	idx = 0;
	idx2 = 5;
	while (envp[mark][idx2])
	{
		path[idx] = envp[mark][idx2];
		idx++;
		idx2++;
	}
	path[idx] = 0;
	return (path);
}

// 유효한 cmd_path만 반환
char	*mk_cmdpath(char *cmd, char *path)
{
	char	*full_path;
	char	*cmd_path;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (0);
	cmd_path = ft_strjoin(full_path, cmd);
	free(full_path);
	if (!cmd_path)
		return (0);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	else
	{
		free(cmd_path);
		return (0);
	}
}
// PATH 경로 중에서 유효한 cmd경로가 있는 경우에만 반환
char	*find_path(char *cmd, char **envp)
{
	char 	*path;
	char	**pathlst;
	char	*cmd_path;
	int		idx;

	path = mk_path(envp);
	if (!path)
		return (0);
	pathlst = ft_split(path, ':');
	free(path);
	if (!pathlst)
		return (0);
	idx = 0;
	while (pathlst[idx])
	{
		cmd_path = mk_cmdpath(cmd, pathlst[idx]);
		if (cmd_path)
		{
			free_lst(pathlst);
			return (cmd_path);
		}
		idx++;
	}
	free_lst(pathlst);
	return (0);
}

// 유효한 path가 있으면 실행 없으면, cmd없다는 메세지 내보내기
void	ft_execve(t_process *proc, char **envp)
{
	char	*cmd;
	char	*cmd_path;
	char	**arg;

	cmd = proc->files->data;
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		send_sigusr2();
	arg = mk_arg(proc);
	execve(cmd_path, arg, envp); // arg[0]과 cmd_path가 같지 않아도 되는지? 만약 같아야 된다면 mk_arg 변경 필요
}

// file->data를 모아서 char **arg를 만들어 줌
char	**mk_arg(t_process *proc)
{
	t_file	*file;
	char	**arg;
	int		file_len;
	int		idx;

	file = proc->files;
	file_len = ft_filelen(file);
	arg = (char **)malloc(sizeof(char *) * (file_len + 1));
	if (!arg)
		send_sigusr1();
	idx = 0;
	while (file)
	{
		arg[idx] = ft_strdup(file->data);
		if (!arg[idx])
			send_sigusr1();
		idx++;
		file = file->next;
	}
	arg[idx] = 0;
	return (arg);
}

void	execute(t_envi	*envi, char ***envp)
{
	t_process	*proc;
	int			proc_num;
	// int			pipe_fd[2];
	pid_t		pid;

	proc = envi->procs;
	proc_num = proc_len(proc);
	if (proc_num == 1)
	{
		if (ck_is_builtin(proc))
			exc_builtin(proc, envp);
		else
		{
			pid = fork();
			if (pid == -1)
				handle_error(2); // 고치기
			else if (pid == 0)
				ft_execve(proc, *envp);
			else
				wait(NULL);
		}
	}
	// else
	// {
	// 	pipe(pipe_fd);
	// 	while (proc)
	// 	{
	// 		pid = fork();
	// 		if (pid == -1)
	// 			handle_error(2);
	// 		else if (pid == 0)
	// 		{
	// 			if (ck_is_builtin(proc))
	// 				exc_builtin(proc, envp);
	// 			else
	// 				ft_execve(proc, *envp);
	// 		}
	// 		else
	// 			wait(NULL);
	// 	}
	// 	proc = proc->next;
	// }
}
