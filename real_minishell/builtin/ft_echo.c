/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:19:14 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/09 21:07:47 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		flag;

	if (!file || ft_strncmp(file->data, ".heredoctmp", 12) == 0)
	{
		printf("\n");
		return (0);
	}
	rem = over_opt(file);
	flag = 1;
	if (file != rem)
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
