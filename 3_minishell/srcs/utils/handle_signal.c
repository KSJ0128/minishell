/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:54:58 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/04 18:24:56 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl+c 프롬프트 출력 방지
void	set_termios(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	reset_termios(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	handle_signal(int sig)
{
	global_sig = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	hello_eof(void)
{
	printf("\033[1A\033[12Cexit\n");
	exit(0);
}
