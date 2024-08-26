/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:54:58 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/24 22:32:10 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigusr1(int sig)
{
	signal(sig, SIG_IGN);
	printf("Error : Malloc Error.\n");
	exit(1);
}

void	handle_sigusr2(int sig) // erorr msg가 두 번 발생함
{
	signal(sig, SIG_IGN);
	printf("Error: command not found\n");
	exit(0);
}

void	send_sigusr1(void)
{
	kill(0, SIGUSR1);
}

void	send_sigusr2(void)
{
	kill(0, SIGUSR2);
}