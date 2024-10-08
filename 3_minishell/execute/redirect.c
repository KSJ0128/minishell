/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 18:17:24 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_file_in_heredoc(t_file *file)
{
	t_file	*new;
	int		fd;

	if (!file)
		return (-1);
	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		send_errmsg_in("minishell", " : Malloc error\n", 1);
	if (g_sig == 0)
		new->data = ft_strdup(".heredoctmp");
	else
	{
		new->data = ft_strdup(".wrongway");
		fd = open("/dev/null", O_WRONLY);
		dup2(fd, 2);
		close(fd);
	}
	if (!new->data)
		send_errmsg_in("minishell", " : Malloc error\n", 1);
	new->next = NULL;
	while (file->next)
		file = file->next;
	file->next = new;
	return (0);
}

int	here_doc(char *del, t_file *file, char **envp, int std_in)
{
	char	*buffer;
	int		fd;
	int		len;

	signal(SIGINT, handle_signal2);
	signal(SIGQUIT, handle_signal2);
	fd = open(".heredoctmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		send_errmsg_in("minishell", " : File didn't open. Sorry\n", 1);
	while (g_sig == 0)
	{
		buffer = get_next_line(std_in);
		if (!buffer)
			break ;
		len = ft_strlen(del);
		if (ft_strncmp(buffer, del, len) == 0 && buffer[len] == '\n')
		{
			free_str(&buffer);
			break ;
		}
		expand_heredoc(envp, &buffer);
		write(fd, buffer, ft_strlen(buffer));
		free_str(&buffer);
	}
	return (push_file_in_heredoc(file));
}

void	except_heredoc(t_redir *redir)
{
	int		fd;

	if (redir->type == 1 || redir->type == 3)
	{
		if (redir->type == 1)
			fd = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			send_errmsg(redir->data, ": No such file or directory\n", 1);
		if (dup2(fd, 1) == -1)
			send_errmsg("minishell", " : failed to duplicate fd\n", 1);
		close(fd);
	}
	else if (redir->type == 2)
	{
		fd = open(redir->data, O_RDONLY);
		if (fd == -1)
			send_errmsg(redir->data, ": No such file or directory\n", 1);
		if (dup2(fd, 0) == -1)
			send_errmsg("minishell", " : failed to duplicate fd\n", 1);
		close(fd);
	}
}

void	ft_redirect(t_redir *redir, t_file *file, char **join_envp, int std_in)
{
	while (redir && g_sig == 0)
	{
		except_heredoc(redir);
		if (redir->type == 4)
			here_doc(redir->data, file, join_envp, std_in);
		redir = redir->next;
	}
}
