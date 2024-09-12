/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:37:11 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/10 14:47:53 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	idx = -1;
	while (++idx < len)
	{
		if (find_str((*envp)[idx], strlst[0]))
		{
			if (strlst[1])
			{
				free_str(&(*envp)[idx]);
				(*envp)[idx] = ft_strdup(str);
				if (!(*envp)[idx])
					handle_error(-1);
			}
			break ;
		}
	}
	free_lst(&strlst);
	return (idx < len);
}

void	export_only(char ***envp)
{
	int	idx;

	idx = 0;
	while ((*envp)[idx])
	{
		if (ft_strncmp((*envp)[idx], "?=", 2) != 0)
			print_envp((*envp)[idx]);
		idx++;
	}
}

int	ft_export(t_file *file, char ***envp)
{
	char	**new_envp;
	int		flag;

	if (!file)
		export_only(envp);
	flag = 0;
	while (file)
	{
		if (!ck_export_valid(file->data))
		{
			flag = send_errmsg_in(file->data, ": not a valid identifier\n", 1);
			file = file->next;
			continue ;
		}
		if (!join_envp(envp, file->data))
		{
			new_envp = add_envp(*envp, file->data);
			free_lst(envp);
			*envp = new_envp;
		}
		file = file->next;
	}
	return (flag);
}
