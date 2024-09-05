/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:24:15 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/05 20:34:06 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_all(int (*dup_fd)[3])
{
	(*dup_fd)[0] = dup(0);
	(*dup_fd)[1] = dup(1);
	(*dup_fd)[2] = dup(2);
}

int	dup2_all(int (*dup_fd)[3], int stat)
{
	dup2((*dup_fd)[0], 0);
	dup2((*dup_fd)[1], 1);
	dup2((*dup_fd)[2], 2);
	close((*dup_fd)[0]);
	close((*dup_fd)[1]);
	close((*dup_fd)[2]);
	return (stat);
}
