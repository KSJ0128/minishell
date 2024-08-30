/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:18:12 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/29 13:12:33 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_val(int *len, int *idx, int *idx2, char **envp)
{
	if (!envp)
		*len = 0;
	else
		*len = ft_lstlen(envp);
	*idx = 0;
	*idx2 = 0;
}

void	ft_unset(char ***envp, t_file *file)
{
	char	**tmp;
	int		len;
	int		idx;
	int		idx2;

	if (!file)
		return ;
	init_val(&len, &idx, &idx2, *envp);
	tmp = (char **)malloc(sizeof(char *) * len);
	if (!tmp)
		handle_error(-1); // error
	while (idx < len - 1) // envp가 1일순 없으니까 가능할거라는 믿음
	{
		if (!find_str((*envp)[idx2], file->data))
		{
			tmp[idx] = ft_strdup((*envp)[idx2]);
			if (!tmp[idx])
				handle_error(-1);
			idx++;
		}
		idx2++;
	}
	tmp[idx] = 0;
	free_lst(*envp);
	*envp = tmp;
}
