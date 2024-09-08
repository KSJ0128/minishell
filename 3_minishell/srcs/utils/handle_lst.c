/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:22:28 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/08 14:04:47 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
