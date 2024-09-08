/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:49:14 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 14:03:08 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ck_is_builtin(t_process *proc)
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

int	exec_builtin(t_process *proc, char ***envp)
{
	char	*cmd;
	t_file	*file;
	int		stat;

	cmd = proc->files->data;
	file = proc->files->next;
	stat = 0;
	if (ft_strncmp("echo", cmd, 5) == 0)
		stat = ft_echo(file);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		stat = ft_pwd();
	else if (ft_strncmp("cd", cmd, 3) == 0)
		stat = ft_cd(file, envp);
	else if (ft_strncmp("export", cmd, 7) == 0)
		stat = ft_export(file, envp);
	else if (ft_strncmp("env", cmd, 4) == 0)
		stat = ft_env(*envp);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		stat = ft_unset(envp, file);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		ft_exit(file);
	else
		return (stat);
	return (stat);
}

int	ck_export_valid(char *name)
{
	int	idx;

	idx = 0;
	if (name[idx] >= '0' && name[idx] <= '9')
		return (0);
	while (name[idx] != '=' && name[idx])
	{
		if (name[idx] >= 'a' && name[idx] <= 'z')
			idx++;
		else if (name[idx] >= 'A' && name[idx] <= 'Z')
			idx++;
		else if (name[idx] >= '0' && name[idx] <= '9')
			idx++;
		else if (name[idx] == '_')
			idx++;
		else
			return (0);
	}
	return (1);
}
