/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/07 11:06:36 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_file_in_heredoc(t_file *file)
{
	t_file	*new;
	int		fd;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		send_errmsg_in(NULL, "Malloc error\n", 1);
	if (global_sig == 0)
		new->data = ft_strdup(".heredoctmp");
	else
	{
		new->data = ft_strdup(".wrongway");
		fd = open("/dev/null", O_WRONLY);
		dup2(fd, 2);
		close(fd);
	}
	if (!new->data)
		send_errmsg_in(NULL, "Malloc error\n", 1);
	new->next = NULL;
	while (file->next)
		file = file->next;
	file->next = new;
}

// error 처리, $환경변수 처리 -> 이건 파싱부에서 하는 게 좋을 듯
void	here_doc(char *del, t_file *file, char **envp)
{
	char	*buffer;
	int		fd;
	int		len;

	signal(SIGINT, handle_signal2);
	signal(SIGQUIT, handle_signal2);
	fd = open(".heredoctmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		send_errmsg_in(NULL, "File didn't open. Sorry\n", 1);
	while (global_sig == 0)
	{
		buffer = get_next_line(0);
		if (!buffer)
			send_errmsg_in(NULL, "Malloc error\n", 1);
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
	push_file_in_heredoc(file);
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
		dup2(fd, 1);
		close(fd);
	}
	else if (redir->type == 2)
	{
		fd = open(redir->data, O_RDONLY);
		if (fd == -1)
			send_errmsg(redir->data, ": No such file or directory\n", 1);
		dup2(fd, 0);
		close(fd);
	}
}

// redirect 을 수행해줌
void	ft_redirect(t_redir *redir, t_file *file, char **join_envp)
{
	while (redir && global_sig == 0)
	{
		except_heredoc(redir);
		if (redir->type == 4)
			here_doc(redir->data, file, join_envp);
		redir = redir->next;
	}
}
