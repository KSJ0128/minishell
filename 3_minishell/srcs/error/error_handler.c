/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:18:59 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/05 18:03:38 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(char *str, int code)
{
	perror(str);
	exit(code);
}

void	handle_error(int num)
{
	if (num == -1)
		printf("Error : Malloc Error.\n");
	else if (num == 0)
		printf("Error : Invalid arguments.\n");
	else if (num == 1)
		printf("Error : Invalid quotes.\n");
	exit (0);
}

void	send_errmsg(char *cmd)
{
	if (!cmd)
	{
		cmd = ft_strdup("minishell");
		write(2, cmd, ft_strlen(cmd));
		free(cmd);
	}
	else
		write(2, cmd, ft_strlen(cmd));
	perror(" ");
}
