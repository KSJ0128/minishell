/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:54 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/09 21:50:22 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	except_heredoc_type1(int type, char *data)
{
	int	fd;

	if (type == 1)
		fd = open(data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (send_errmsg_in("minishell", " : fail to open file\n", 1));
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	except_heredoc_type2(char *data)
{
	int	fd;

	fd = open(data, O_RDONLY);
	if (fd == -1)
		return (send_errmsg_in("minishell", " : fail to open file\n", 1));
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	except_heredoc_one(t_redir *redir)
{
	int		ans;

	ans = 0;
	if (redir->type == 1 || redir->type == 3)
		ans = except_heredoc_type1(redir->type, redir->data);
	else if (redir->type == 2)
		ans = except_heredoc_type2(redir->data);
	return (ans);
}

int	ft_redirect_one(t_redir *redir, t_file *file, char **envp, int std_in)
{
	int	stat;

	stat = 0;
	while (redir && g_sig == 0 && stat == 0)
	{
		stat = except_heredoc_one(redir);
		if (redir->type == 4)
			stat = here_doc(redir->data, file, envp, std_in);
		redir = redir->next;
	}
	return (stat);
}
