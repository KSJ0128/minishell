/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:18:59 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/05 20:39:26 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(int num)
{
	if (num == -1)
		printf("Error : Malloc Error.\n");
	else if (num == 0)
		printf("Error : Invalid arguments.\n");
	else if (num == 1)
		printf("Error : Invalid quotes.\n");
	exit (0); // error 후에 0으로 exit 해도 되는지
}

void	send_errmsg(char *cmd, int exitcode)
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
	exit(exitcode);
}

int	send_errmsg_export(char *cmd, int code)
{
	if (!cmd)
	{
		cmd = ft_strdup("minishell");
		write(2, cmd, ft_strlen(cmd));
		free(cmd);
	}
	else
		write(2, cmd, ft_strlen(cmd));
	write(2, " : not a valid identifier\n", 27);
	return (code);
}
