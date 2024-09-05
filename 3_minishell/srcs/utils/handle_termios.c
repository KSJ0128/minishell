/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:36:01 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/05 14:37:33 by seungbel         ###   ########.fr       */
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
	term.c_lflag |= ICANON;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	hello_eof(void)
{
	printf("\033[1A\033[12Cexit\n");
	exit(0);
}
