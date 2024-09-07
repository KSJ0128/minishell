/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:22:28 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/07 22:20:10 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//  char ** 길이를 재는 함수
int	ft_lstlen(char **lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst[len])
		len++;
	return (len);
}

// file 길이 구해줌
int	ft_filelen(t_file *file)
{
	int	len;

	len = 0;
	while (file)
	{
		file = file->next;
		len++;
	}
	return (len);
}

// process의 길이를 구해줌
int	proc_len(t_process *proc)
{
	int	len;

	len = 0;
	while (proc)
	{
		len++;
		proc = proc->next;
	}
	return (len);
}

// char **lst를 완전히 free해주는 함수
void	free_lst(char **lst)
{
	int	idx;

	idx = 0;
	while (lst[idx])
		free(lst[idx++]);
	free(lst);
}

void	free_arg(int idx, char ***arg)
{
	while (--idx >= 0)
		free((*arg)[idx]);
	free(*arg);
	send_errmsg(NULL, " : Malloc Error\n", 1);
}
