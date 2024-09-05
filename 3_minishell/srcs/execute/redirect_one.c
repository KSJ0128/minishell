/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:54 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/05 17:30:09 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	except_heredoc_one(t_redir *redir)
{
	int		fd;

	if (redir->type == 1 || redir->type == 3)
	{
		if (redir->type == 1)
			fd = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			send_errmsg(redir->data);
			return (1);
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (redir->type == 2)
	{
		fd = open(redir->data, O_RDONLY);
		if (fd == -1)
		{
			send_errmsg(redir->data);
			return (1);
		}
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

int	ft_redirect_one(t_redir *redir, t_file *file)
{
	int	stat;

	stat = 0;
	while (redir && global_sig == 0 && stat == 0)
	{
		stat = except_heredoc_one(redir);
		if (redir->type == 4)
			here_doc(redir->data, file);
		redir = redir->next;
	}
	return (stat);
}
