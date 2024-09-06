/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:20:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/03 16:45:01 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_file *file)
{
	char	*str;
	int		num;

	if (!file)
	{
		printf("exit\n");
		exit(0);
	}
	str = file->data;
	num = ft_atoi(str);
	printf("exit\n");
	exit(num);
}
