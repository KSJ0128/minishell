/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:41:10 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 13:14:08 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

void	free_lst(char ***lst)
{
	int	idx;

	idx = 0;
	while ((*lst)[idx])
	{
		free((*lst)[idx]);
		(*lst)[idx] = NULL;
		idx++;
	}
	free(*lst);
	*lst = NULL;
}

void	free_arg(int idx, char ***arg)
{
	while (--idx >= 0)
		free((*arg)[idx]);
	free(*arg);
	*arg = NULL;
	send_errmsg("minishell", " : Malloc Error\n", 1);
}
