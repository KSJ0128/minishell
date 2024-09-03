/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:54:58 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/03 21:26:02 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl+c 프롬프트 출력 방지
void	set_termios(t_termios *term)
{
	tcgetattr(STDIN_FILENO, &term->old_term);
	tcgetattr(STDIN_FILENO, &term->new_term);
	term->new_term.c_lflag &= ~ICANON;
	term->new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
}


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

void	handle_sigint()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}