/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:32:07 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/07 11:33:23 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		idx;
	char	*key;

	idx = 0;
	if (str[idx] == '$')
		return (ft_strdup("$"));
	while (str[idx] != '\0' && \
	(ft_isalnum(str[idx]) || str[idx] == '_' || str[idx] == '?'))
		idx++;
	if (idx == 0)
		return (NULL);
	key = (char *)malloc(idx + 1);
	if (!key)
		handle_error(-1);
	ft_strlcpy(key, str, idx + 1);
	return (key);
}

char	*get_value(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '=')
		idx++;
	return (str + idx + 1);
}

