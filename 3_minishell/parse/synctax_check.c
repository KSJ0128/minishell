/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synctax_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:17:20 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/08 21:58:00 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line, t_envi *envi)
{
	int	idx;

	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '\'' && !(envi->quote[DOUBLE]))
			envi->quote[SINGLE] ^= 1;
		else if (line[idx] == '\"' && !(envi->quote[SINGLE]))
			envi->quote[DOUBLE] ^= 1;
		idx++;
	}
	if (envi->quote[SINGLE] || envi->quote[DOUBLE])
		return (ERROR_QUOTE);
	return (SUCCESS);
}

int	is_quote(char c, t_envi *envi)
{
	if (c == '\'' && !(envi->quote[DOUBLE]))
	{
		envi->quote[SINGLE] ^= 1;
		return (SUCCESS);
	}
	else if (c == '\"' && !(envi->quote[SINGLE]))
	{
		envi->quote[DOUBLE] ^= 1;
		return (SUCCESS);
	}
	return (FALSE);
}

int	is_deli(char *line, t_envi *envi, int idx)
{
	if (envi->quote[SINGLE] || envi->quote[DOUBLE])
		return (FALSE);
	if ((line[idx] >= 9 && line[idx] <= 13) || line[idx] == 32)
		return (TRUE);
	else if (line[idx] == ' ' || line[idx] == '|' || line[idx] == '<' || \
		line[idx] == '>' || line[idx] == '\0')
		return (TRUE);
	return (FALSE);
}

int	check_deli(char *line, t_envi *envi, int start, int idx)
{
	if ((line[idx] == '<' && line[idx + 1] == '<') || \
		(line[idx] == '>' && line[idx + 1] == '>'))
	{
		add_token(line, envi, start, idx + 2);
		return (DELI_REDIR);
	}
	else if (line[idx] == '|' || line[idx] == '<' || line[idx] == '>')
	{
		add_token(line, envi, idx, idx + 1);
		return (DELI_ETC);
	}
	return (DELI_ETC);
}
