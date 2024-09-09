/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:28:43 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 18:18:08 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mk_buf(char **buf, int fd, int *read_num)
{
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buf)
	{
		*read_num = -1;
		return (-1);
	}
	*read_num = read(fd, *buf, BUFFER_SIZE);
	if (*read_num <= 0)
	{
		free(*buf);
		*buf = NULL;
		return (*read_num);
	}
	else
		(*buf)[*read_num] = '\0';
	return (*read_num);
}

static void	re_rem(char **rem, char **ans, int bk_idx)
{
	char	*temp;
	int		rem_len;

	rem_len = ft_strlen(*rem);
	if (bk_idx + 1 < rem_len)
	{
		temp = *rem;
		*rem = ft_strdup(temp + bk_idx + 1);
		free(temp);
		temp = NULL;
		if (!*rem)
		{
			free(*ans);
			*ans = NULL;
		}
	}
	else
	{
		free(*rem);
		*rem = NULL;
	}
}

static char	*ext_ans(char **rem, int bk_idx, int read_num)
{
	char	*ans;

	if (!*rem && read_num == 0)
		return (0);
	if (bk_idx == -1 && read_num < BUFFER_SIZE)
		bk_idx = ft_strlen(*rem);
	ans = ft_substr(*rem, 0, (size_t)bk_idx + 1);
	if (!ans)
	{
		free(*rem);
		*rem = NULL;
		return (0);
	}
	re_rem(rem, &ans, bk_idx);
	return (ans);
}

static int	add_rem(char **rem, char **buf)
{
	char	*temp;

	if (*rem)
	{
		temp = *rem;
		*rem = ft_strjoin(temp, *buf);
		free(temp);
		temp = NULL;
		free(*buf);
		*buf = NULL;
		if (!*rem)
			return (0);
	}
	else
	{
		*rem = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
		if (!*rem)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*buf;
	int			bk_idx;
	int			read_num;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_num = BUFFER_SIZE;
	if (ft_strchr_num(rem, '\n', &bk_idx) >= 0)
		return (ext_ans(&rem, bk_idx, read_num));
	while (mk_buf(&buf, fd, &read_num) > 0)
	{
		if (!add_rem(&rem, &buf))
			return (0);
		if (ft_strchr_num(rem, '\n', &bk_idx) >= 0 || read_num < BUFFER_SIZE)
			return (ext_ans(&rem, bk_idx, read_num));
	}
	if (read_num < 0)
	{
		free(rem);
		rem = NULL;
		return (0);
	}
	return (ext_ans(&rem, bk_idx, read_num));
}
