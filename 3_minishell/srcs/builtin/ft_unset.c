/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:18:12 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 18:17:43 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ck_envp(char **envp, t_file *file)
{
	int	idx;
	int	lstlen;

	idx = 0;
	lstlen = ft_lstlen(envp);
	while (idx < lstlen)
	{
		if (find_str(envp[idx], file->data))
			return (1);
		idx++;
	}
	return (0);
}

void	init_val(int *len, int *idx, int *idx2, char **envp)
{
	if (!envp)
		*len = 0;
	else
		*len = ft_lstlen(envp);
	*idx = 0;
	*idx2 = 0;
}

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

int	ft_unset(char ***envp, t_file *file)
{
	char	**tmp;
	int		len;
	int		idx;
	int		idx2;

	if (!file || !ck_envp(*envp, file))
		return (0);
	init_val(&len, &idx, &idx2, *envp);
	tmp = (char **)malloc(sizeof(char *) * len);
	if (!tmp)
		return (1);
	while (idx2 < len)
	{
		if (!find_str((*envp)[idx2], file->data))
		{
			tmp[idx] = ft_strdup((*envp)[idx2]);
			if (!tmp[idx++])
				return (free_tmp(idx, &tmp));
		}
		idx2++;
	}
	tmp[idx] = 0;
	free_lst(envp);
	*envp = tmp;
	return (0);
}
