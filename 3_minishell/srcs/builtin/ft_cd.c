/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:10:21 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/29 12:01:39 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_file *file)
{
	char	*path;

	if (!file)
		return ;
	path = file->data; // ~가 path에 포함되어 있을 경우 처리
	if (chdir(path) != 0)
		perror("cd Error:");
}
