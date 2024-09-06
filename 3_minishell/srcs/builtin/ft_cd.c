/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:10:21 by seungbel          #+#    #+#             */
/*   Updated: 2024/09/02 20:58:42 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_file *file)
{
	char	*path;

	if (!file)
		return (1);
	path = file->data;
	if (ft_strncmp(path, "~", 2) == 0)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		perror("Invalid path");
		return (1);
	}
	return (0);
}
