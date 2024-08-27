/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:52:18 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/27 22:45:20 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *del) // 임시 파일 만들고, 지워줘야 함
{
	char	*buffer;
	int		fd;

	fd = open(".heredoctmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ; // error 처리
	dup2(fd, 1);
	close(fd);
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
		printf("%s", buffer);
		free(buffer);
	}
}

// redirect 을 수행해줌
void	ft_redirect(t_redir *redir)
{
	int		fd;

	while (redir)
	{
		if (redir->type == 1 || redir->type == 3) // > , >>
		{
			if (redir->type == 1)
				fd = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				kill(0, SIGUSR2);
			dup2(fd, 1);
			close(fd);
		}
		else if (redir->type == 2) // <
		{
			fd = open(redir->data, O_RDONLY);
			if (fd == -1)
				kill(0, SIGUSR2);
			dup2(fd, 0);
			close(fd);
		}
		else // <<
			here_doc(redir->data);
		redir = redir->next;
	}
}
