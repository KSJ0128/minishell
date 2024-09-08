/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:46:57 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 14:04:02 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_pointer(char **envp)
{
	int		mark;

	mark = 0;
	while (envp[mark])
	{
		if (ft_strncmp("PATH=", envp[mark], 5) == 0)
			return (envp[mark] + 5);
		mark++;
	}
	return (0);
}

char	*mk_cmdpath(char *cmd, char *path)
{
	char	*full_path;
	char	*cmd_path;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		send_errmsg(NULL, " : Malloc Error\n", 1);
	cmd_path = ft_strjoin(full_path, cmd);
	free_str(&full_path);
	if (!cmd_path)
		send_errmsg(NULL, " : Malloc Error\n", 1);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	else
	{
		free_str(&cmd_path);
		return (0);
	}
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	**pathlst;
	char	*cmd_path;
	int		idx;

	path = path_pointer(envp);
	if (!path)
		return (0);
	pathlst = ft_split(path, ':');
	free_str(&path);
	if (!pathlst)
		send_errmsg(NULL, " : Malloc Error\n", 1);
	idx = 0;
	while (pathlst[idx])
	{
		cmd_path = mk_cmdpath(cmd, pathlst[idx]);
		if (cmd_path)
		{
			free_lst(&pathlst);
			return (cmd_path);
		}
		idx++;
	}
	free_lst(&pathlst);
	return (0);
}

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
		send_errmsg(NULL, " : Malloc Error\n", 1);
	idx = 0;
	while (file)
	{
		if (idx == 0)
			arg[idx] = ft_strdup(cmd_path);
		else
			arg[idx] = ft_strdup(file->data);
		if (!arg[idx])
			free_arg(idx, &arg);
		idx++;
		file = file->next;
	}
	arg[idx] = 0;
	return (arg);
}

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
