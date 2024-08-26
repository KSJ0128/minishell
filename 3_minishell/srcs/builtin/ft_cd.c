/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:10:21 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/20 11:26:29 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_file *file)
{
	char	*path;

	if (!file)
		return ;
	path = file->data;
	if (chdir(path) != 0)
		perror("cd Error:");
}