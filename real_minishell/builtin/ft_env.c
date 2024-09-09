/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:49:51 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/09 12:50:12 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_file *file, char **envp)
{
	int		idx;
	int		len;
	char	**tmp;
	char	*cmd;

	cmd = 0;
	if (file && file->data)
	{
		cmd = file->data;
		return (send_errmsg_in(cmd, " : No such file or directory\n", 127));
	}
	len = ft_lstlen(envp);
	idx = 0;
	while (idx < len)
	{
		tmp = ft_split(envp[idx], '=');
		if (tmp[1] && ft_strncmp(envp[idx], "?=", 2))
			printf("%s\n", envp[idx]);
		free_lst(&tmp);
		idx++;
	}
	return (0);
}
