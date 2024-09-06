/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:19:14 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/05 17:06:04 by seungbel         ###   ########.fr       */
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
		idx++;
		while ((rem->data[idx]))
		{
			if ((rem->data)[idx] != 'n')
				return (rem);
			idx++;
		}
		rem = rem->next;
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
		return (0);
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
