/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:33:50 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/27 21:09:34 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_num(const char *s, int c, int *bk_idx)
{
	int	idx;

	idx = 0;
	if (!s)
	{
		*bk_idx = -1;
		return (-1);
	}
	while (s[idx])
	{
		if (s[idx] == c)
		{
			*bk_idx = idx;
			return (idx);
		}
		idx++;
	}
	if (s[idx] == c)
	{
		*bk_idx = idx;
		return (idx);
	}
	*bk_idx = -1;
	return (-1);
}
