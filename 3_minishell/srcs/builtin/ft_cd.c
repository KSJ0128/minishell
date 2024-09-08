/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:10:21 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 13:14:07 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *env, char **envp)
{
	int	idx;
	int	len;

	idx = 0;
	len = ft_strlen(env);
	while (envp[idx])
	{
		if (ft_strncmp(env, envp[idx], len) == 0 && envp[idx][len] == '=')
			return (&envp[idx][++len]);
		idx++;
	}
	return (0);
}

int	ck_is_directory(char *path)
{
	struct stat	path_stat;

	if (!path
		||ft_strncmp(path, "..", 3) == 0 || ft_strncmp(path, ".", 2) == 0
		|| ft_strncmp(path, "~", 2) == 0 || ft_strncmp(path, "-", 2) == 0)
		return (1);
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

int	change_pwds(char ***envp)
{
	char	*pwd;
	char	*oldpwd;
	char	*now;

	now = getcwd(NULL, 0);
	if (!now)
		return (0);
	pwd = ft_strjoin("PWD=", now);
	if (!pwd)
		return (0);
	free_str(&now);
	oldpwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", *envp));
	if (!oldpwd)
		return (0);
	join_envp(envp, oldpwd);
	join_envp(envp, pwd);
	free_str(&pwd);
	free_str(&oldpwd);
	return (1);
}

int	ft_cd(t_file *file, char ***envp)
{
	char	*path;

	if (!file)
		path = 0;
	else
		path = file->data;
	if (ck_is_directory(path) == 1)
	{
		if (!path || ft_strncmp(path, "~", 2) == 0)
			path = ft_getenv("HOME", *envp);
		else if (ft_strncmp(path, "-", 2) == 0)
			path = ft_getenv("OLDPWD", *envp);
		if (chdir(path) != 0)
			return (send_errmsg_in(path, ": Permission denied\n", 1));
		else
			if (!change_pwds(envp))
				return (send_errmsg_in("minishell", "Malloc error\n", 1));
	}
	else if (ck_is_directory(path) == 0)
		return (send_errmsg_in(path, ": Not a directory\n", 1));
	else if (ck_is_directory(path) == -1)
		return (send_errmsg_in(path, ": No such file or directory\n", 1));
	return (0);
}
