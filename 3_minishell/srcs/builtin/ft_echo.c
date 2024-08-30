/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:19:14 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/22 14:03:18 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 옵션이 있는지 없는지 판단, 있다면 옵션 아닌 부분을 return 해줌
static t_file	*over_opt(t_file *file)
{
	t_file	*rem;
	int		idx;

	rem = file;
	while (rem)
	{
		idx = 0;
		if ((rem->data)[idx] != '-')
			return (rem);
		while (1)
		{
			idx++;
			if ((rem->data)[idx] != 'n')
				return (rem);
			if (!(rem->data)[idx + 1])
			{
				rem = file->next;
				break ;
			}
		}
	}
	return (rem);
}

int	ft_echo(t_file *file)
{
	t_file	*rem;
	t_file	*first;
	int		flag;

	if (!file)
	{
		printf("\n");
		return (-1);
	}
	first = file;
	rem = over_opt(file);
	flag = 1;
	if (first != rem)
		flag = 0;
	while (rem)
	{
		printf("%s", rem->data);
		if (rem->next)
			printf(" ");
		rem = rem->next;
	}
	if (flag)
		printf("\n");
	return (0);
}
