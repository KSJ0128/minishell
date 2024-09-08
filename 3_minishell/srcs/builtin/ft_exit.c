/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:20:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 18:16:32 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_file *file)
{
	int		num;
	int		idx;

	if (!file)
	{
		printf("exit\n");
		exit(0);
	}
	idx = 0;
	if ((file->data)[idx] == '-' || (file->data)[idx] == '+')
		idx++;
	while ((file->data)[idx])
	{
		if (!ft_isdigit((file->data)[idx++]))
		{
			write(2, (file->data), ft_strlen((file->data)));
			write(2, " : numeric argument required\n", 29);
			exit(-1);
		}
	}
	if (file->next)
		send_errmsg("exit", " : too many arguments\n", 1);
	num = ft_atoi((file->data));
	exit(num);
}
