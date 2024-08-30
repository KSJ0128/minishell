/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:49:14 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/29 12:01:31 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin 명령어인지 체크
int	ck_is_builtin(t_process *proc)
{
	char	*cmd;

	cmd = proc->files->data;
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (2);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		return (3);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (4);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (5);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (6);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (7);
	else
		return (0);
}

// bulitin 명령어 실행
void	exec_builtin(t_process *proc, char ***envp)
{
	char	*cmd;
	t_file	*file;

	cmd = proc->files->data;
	file = proc->files->next;
	if (ft_strncmp("echo", cmd, 5) == 0)
		ft_echo(file);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		ft_pwd();
	else if (ft_strncmp("cd", cmd, 3) == 0)
		ft_cd(file);
	else if (ft_strncmp("export", cmd, 7) == 0)
		ft_export(file, envp);
	else if (ft_strncmp("env", cmd, 4) == 0)
		ft_env(*envp);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		ft_unset(envp, file);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		ft_exit(file);
	else
		return ;
}
