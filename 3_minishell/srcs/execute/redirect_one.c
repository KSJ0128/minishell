/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:54 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 13:01:16 by seungbel         ###   ########.fr       */
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
	{
		if (!data)
		{
			data = ft_strdup("minishell");
			write(2, data, ft_strlen(data));
			free_str(&data);
		}
		else
			write(2, data, ft_strlen(data));
		perror(" ");
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	except_heredoc_type2(char *data)
{
	int	fd;

	fd = open(data, O_RDONLY);
	if (fd == -1)
	{
		if (!data)
		{
			data = ft_strdup("minishell");
			write(2, data, ft_strlen(data));
			free_str(&data);
		}
		else
			write(2, data, ft_strlen(data));
		perror(" ");
		return (1);
	}
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
