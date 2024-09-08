/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:43:31 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 14:56:44 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exitcode(pid_t last, int proc_num)
{
	int	stat;
	int	exitcode;

	while (proc_num > 0)
	{
		if (last == wait(&stat))
		{
			if (WIFEXITED(stat))
				exitcode = WEXITSTATUS(stat);
			else
				exitcode = 128 + WTERMSIG(stat);
		}
		proc_num--;
	}
	return (exitcode);
}

void	record_exitcode(int code, char ***envp)
{
	char	*code_str;
	char	*ans;

	if (code == -1)
		code = 0;
	code_str = ft_itoa(code);
	ans = ft_strjoin("?=", code_str);
	join_envp(envp, ans);
	free_str(&code_str);
	free_str(&ans);
}
