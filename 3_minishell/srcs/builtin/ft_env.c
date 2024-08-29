/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:49:51 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/29 12:01:55 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 뒤에 명령어는 그냥 무시하도록 구현했는데, 그렇게 해도 될런지
void	ft_env(char **envp)
{
	int		idx;
	int		len;
	char	**tmp;

	len = ft_lstlen(envp);
	idx = 0;
	while (idx < len)
	{
		tmp = ft_split(envp[idx], '=');
		if (tmp[1])
			printf("%s\n", envp[idx]);
		free_lst(tmp);
		idx++;
	}
}
