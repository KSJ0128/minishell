/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:49:51 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 14:03:21 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **envp)
{
	int		idx;
	int		len;
	char	**tmp;

	len = ft_lstlen(envp);
	idx = 0;
	while (idx < len)
	{
		tmp = ft_split(envp[idx], '=');
		if (tmp[1] && ft_strncmp(envp[idx], "?=", 2))
			printf("%s\n", envp[idx]);
		free_lst(&tmp);
		idx++;
	}
	return (0);
}
