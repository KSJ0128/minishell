/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:18:12 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/10 13:14:57 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_tmp(int idx, char ***tmp)
{
	while (--idx >= 0)
	{
		free((*tmp)[idx]);
		(*tmp)[idx] = NULL;
	}
	free(*tmp);
	*tmp = NULL;
	return (1);
}

int	remove_envp(char ***envp, char ***tmp, t_file *file)
{
	int	idx;
	int	idx2;

	idx = 0;
	idx2 = 0;
	while ((*envp)[idx2])
	{
		if (!find_str((*envp)[idx2], file->data))
		{
			(*tmp)[idx] = ft_strdup((*envp)[idx2]);
			if (!(*tmp)[idx++])
				return (free_tmp(idx, tmp));
		}
		idx2++;
	}
	(*tmp)[idx] = 0;
	free_lst(envp);
	*envp = *tmp;
	return (0);
}

int	ft_unset(char ***envp, t_file *file)
{
	char	**tmp;
	int		len;
	int		flag;
	char	*cmd;

	if (!file)
		return (0);
	cmd = 0;
	flag = 0;
	while (file)
	{
		if (!ck_export_valid(file->data))
		{
			cmd = file->data;
			flag = send_errmsg_in(cmd, ": not a valid identifier\n", 1);
			file = file->next;
			continue ;
		}
		len = ft_lstlen(*envp);
		tmp = (char **)malloc(sizeof(char *) * len);
		if (!tmp || remove_envp(envp, &tmp, file))
			send_errmsg("minishell", " : malloc Error\n", 1);
		file = file->next;
	}
	return (flag);
}
