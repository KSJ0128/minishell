/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:20:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/05 18:05:38 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_file *file)
{
	char	*str;
	int		num;
	int		idx;

	if (!file)
	{
		printf("exit\n");
		exit(0);
	}
	str = file->data;
	idx = 0;
	if (str[idx] == '-' || str[idx] == '+')
		idx++;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx++]))
		{
			write(2, str, ft_strlen(str));
			write(2, " : numeric argument required\n", 29);
			exit(-1);
		}
	}
	num = ft_atoi(str);
	printf("exit %d\n", num);
	exit(num);
}
