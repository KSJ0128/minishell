/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:54:58 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/02 06:32:13 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigusr1(int sig)
{
	signal(sig, SIG_IGN);
	printf("Error : Malloc Error.\n");
	return ;
}

void	handle_sigusr2(int sig) // erorr msg가 두 번 발생함
{
	signal(sig, SIG_IGN);
	printf("Error: Son always breaks his parent's hearts\n");
	return ;
}
