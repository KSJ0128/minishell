/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:49:51 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/02 18:46:42 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 뒤에 명령어는 그냥 무시하도록 구현했는데, 그렇게 해도 될런지
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
		free_lst(tmp);
		idx++;
	}
	return (0);
}
