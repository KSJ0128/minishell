/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:57:38 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/10 14:31:05 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_quote(char *line)
{
	int	idx;
	int	s_quote;
	int	d_quote;

	idx = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '\'' && !(d_quote))
			s_quote ^= 1;
		else if (line[idx] == '\"' && !(s_quote))
			d_quote ^= 1;
		idx++;
	}
	if (s_quote || d_quote)
	{
		printf("Error : Invalid quotes.\n");
		free(line);
		return (ERROR_QUOTE);
	}
	return (SUCCESS);
}

void	delete_token(t_envi *envi, t_token **now, t_token **prev)
{
	t_token	*next;

	if (*prev)
		(*prev)->next = (*now)->next;
	free((*now)->data);
	if ((*now) == envi->tokens)
		envi->tokens = (*now)->next;
	next = (*now)->next;
	free(*now);
	(*now) = next;
}

void	print_envp(char *str)
{
	char	*key;
	char	*value;

	key = get_key(str);
	value = get_value(str);
	printf("%s", key);
	if (*value)
	{
		printf("=\"");
		printf("%s\"", value);
	}
	printf("\n");
	free(key);
}
