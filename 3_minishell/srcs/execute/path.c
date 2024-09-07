/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:46:57 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/07 17:27:53 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PATH를 가진 str을 만듦
char	*mk_path(char **envp)
{
	char	*path;
	int		mark;
	int		idx;
	int		idx2;

	mark = 0;
	while (envp[mark])
	{
		if (ft_strncmp("PATH=", envp[mark], 5) == 0)
			break ;
		mark++;
	}
	path = (char *)malloc(sizeof(char) * ((int)ft_strlen(envp[mark]) - 4));
	if (!path)
		return (0); // error 체크
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
	char	*path;
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

// file->data를 모아서 char **arg를 만들어 줌
char	**mk_arg(t_process *proc, char *cmd_path)
{
	t_file	*file;
	char	**arg;
	int		file_len;
	int		idx;

	file = proc->files;
	file_len = ft_filelen(file);
	arg = (char **)malloc(sizeof(char *) * (file_len + 1));
	if (!arg)
		return (0);
	idx = 0;
	while (file)
	{
		if (idx == 0)
			arg[idx] = ft_strdup(cmd_path);
		else
			arg[idx] = ft_strdup(file->data);
		if (!arg[idx])
			return (free_arg(idx, &arg));
		idx++;
		file = file->next;
	}
	arg[idx] = 0;
	return (arg);
}

// 유효한 path가 있으면 실행 없으면, cmd없다는 메세지 내보내기
void	ft_execve(t_process *proc, char **envp)
{
	char		*cmd;
	char		*cmd_path;
	char		**arg;
	struct stat	cmd_stat;

	cmd = proc->files->data;
	cmd_path = 0;
	if (stat(cmd, &cmd_stat) == 0)
	{
		if (S_ISDIR(cmd_stat.st_mode))
			send_errmsg(cmd, " : is a directory\n", 126);
		else if (S_ISREG(cmd_stat.st_mode))
		{
			if (access(cmd, X_OK) == 0)
				cmd_path = cmd;
			else
				send_errmsg(cmd, " : Permission denied\n", 126);
		}
	}
	else
		cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		send_errmsg(cmd, " : command not found\n", 127);
	arg = mk_arg(proc, cmd_path);
	execve(cmd_path, arg, envp);
}
