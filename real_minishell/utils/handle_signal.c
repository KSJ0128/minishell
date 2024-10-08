/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:54:58 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 18:17:16 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig = sig;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal2(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	handle_signal3(int sig)
{
	g_sig = sig;
}

void	init_sig_termi(void)
{
	struct termios	term;

	g_sig = 0;
	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void	reset_sig_termi(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	term.c_lflag |= ICANON;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
