/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:37:11 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/09 20:48:38 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envp(char *str)
{
	int		idx;
	int		idx2;
	char	**strlst;

	idx = 0;
	while (str[idx])
	{
		if (str[idx++] == '=')
		{
			strlst = ft_split(str, '=');
			if (!strlst)
				handle_error(-1);
			printf("%s=", strlst[0]);
			idx2 = 1;
			while (strlst[idx2])
				printf("\"%s", strlst[idx2++]);
			free_lst(&strlst);
			printf("\"\n");
			return ;
		}
	}
	printf("%s\n", str);
}

static char	**add_envp(char **envp, char *str)
{
	int		idx;
	char	**new_envp;

	new_envp = (char **)malloc(sizeof(char *) * (ft_lstlen(envp) + 2));
	if (!new_envp)
		handle_error(-1);
	idx = 0;
	while (idx < ft_lstlen(envp))
	{
		new_envp[idx] = ft_strdup(envp[idx]);
		if (!new_envp[idx])
			handle_error(-1);
		idx++;
	}
	new_envp[idx++] = ft_strdup(str);
	if (!new_envp)
		handle_error(-1);
	new_envp[idx] = 0;
	return (new_envp);
}

int	find_str(char *en, char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	if (ft_strncmp(en, str, len) == 0
		&& (en[len] == '\0' || en[len] == '='))
		return (1);
	else
		return (0);
}

int	join_envp(char ***envp, char *str)
{
	char	**strlst;
	int		len;
	int		idx;

	strlst = ft_split(str, '=');
	if (!strlst)
		handle_error(-1);
	len = ft_lstlen(*envp);
	idx = 0;
	while (idx < len)
	{
		if (find_str((*envp)[idx], strlst[0]) && strlst[1])
		{
			free_str(&(*envp)[idx]);
			(*envp)[idx] = ft_strdup(str);
			if (!(*envp)[idx])
				handle_error(-1);
			break ;
		}
		idx++;
	}
	free_lst(&strlst);
	return (idx < len);
}

int	ft_export(t_file *file, char ***envp)
{
	char	**new_envp;
	int		idx;

	idx = -1;
	if (!file)
	{
		while ((*envp)[++idx])
			if (ft_strncmp((*envp)[idx], "?=", 2) != 0)
				print_envp((*envp)[idx]);
	}
	while (file)
	{
		if (!ck_export_valid(file->data))
			return (send_errmsg_in(file->data, ": not a valid identifier\n", 1));
		else
		{
			if (join_envp(envp, file->data))
				return (0);
			new_envp = add_envp(*envp, file->data);
			free_lst(envp);
			*envp = new_envp;
		}
		file = file->next;
	}
	return (0);
}
