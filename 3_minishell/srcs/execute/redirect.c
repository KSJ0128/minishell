/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/06 17:55:43 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_file_in_heredoc(t_file *file)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		handle_error(-1); // error 처리
	new->data = ft_strdup(".heredoctmp");
	if (!new->data)
		return ; // error
	new->next = NULL;
	while (file->next)
		file = file->next;
	file->next = new;
}

void	here_doc(char *del, t_file *file, char **envp) // 임시 파일 만들고, 지워줘야 함
{
	char	*buffer;
	int		fd;

	fd = open(".heredoctmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ; // error 처리
	while (1)
	{
		buffer = get_next_line(0); // error 처리, $환경변수 처리 -> 이건 파싱부에서 하는 게 좋을 듯
		if (!buffer)
			return ; // error 처리
		if (ft_strncmp(buffer, del, ft_strlen(del)) == 0)
		{
			free(buffer);
			break ;
		}
		expand_heredoc(envp, &buffer);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	push_file_in_heredoc(file);
}

void	except_heredoc(t_redir *redir)
{
	int		fd;

	if (redir->type == 1 || redir->type == 3) // > , >>
	{
		if (redir->type == 1)
			fd = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return ;
		dup2(fd, 1);
		close(fd);
	}
	else if (redir->type == 2) // <
	{
		fd = open(redir->data, O_RDONLY);
		if (fd == -1)
			return ;
		dup2(fd, 0);
		close(fd);
	}
}

// redirect 을 수행해줌
void	ft_redirect(t_redir *redir, t_file *file, char **envp)
{
	while (redir)
	{
		except_heredoc(redir);
		if (redir->type == 4)
			here_doc(redir->data, file, envp);
		redir = redir->next;
	}
}
