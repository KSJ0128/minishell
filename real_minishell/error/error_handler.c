/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:18:59 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/09 16:06:46 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(int num)
{
	if (num == -1)
		printf("Error : Malloc Error.\n");
	else if (num == 0)
		printf("Error : Invalid arguments.\n");
	exit(1);
}

void	send_errmsg(char *cmd, char *msg, int exitcode)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	exit(exitcode);
}

int	send_errmsg_in(char *cmd, char *msg, int code)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	return (code);
}
