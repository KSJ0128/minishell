/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:41:14 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/07 11:41:53 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_var(t_token *now, int idx, char c)
{
	if (c == '$')
	{
		change_var(now, ft_itoa(getpid()), idx, idx + 2);
		return (TRUE);
	}
	else if (c == '0')
		return (TRUE);
	else if (c == '!')
		return (TRUE);
	else if (c == '(')
		return (TRUE);
	else
		return (FALSE);
}

void	set_out_quote(char quote, t_envi *envi)
{
	if (envi->quote[SINGLE] == 0 && envi->quote[DOUBLE] == 0)
		envi->out_quote = NULL;
	else if (envi->quote[SINGLE] == 1 && envi->quote[DOUBLE] == 1)
	{
		if (quote == '\'')
			envi->out_quote = '\"';
		else
			envi->out_quote = '\'';
	}
	else
		envi->out_quote = quote;
}
