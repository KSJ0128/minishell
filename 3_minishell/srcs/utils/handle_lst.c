/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:22:28 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 12:48:57 by seojkim          ###   ########.fr       */
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
	while (proc && (proc->files || proc->redirs))
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
