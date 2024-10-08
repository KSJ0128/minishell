/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:07:27 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/09 20:25:51 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(char *line, t_envi *envi, int start, int idx)
{
	t_token	*now;
	t_token	*token;
	char	*str;

	str = ft_strndup(line + start, idx - start);
	if (!str)
		handle_error(-1);
	now = envi->tokens;
	if (now->data == 0)
		now->data = str;
	else
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (!token)
			handle_error(-1);
		token->data = str;
		token->next = 0;
		while (now->next != 0)
			now = now->next;
		now->next = token;
	}
}

void	tokenize(char *line, t_envi *envi)
{
	int	start;
	int	idx;

	start = 0;
	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '\'' || line[idx] == '\"')
			is_quote(line[idx], envi);
		else if (is_deli(line, envi, idx))
		{
			if (start < idx)
				add_token(line, envi, start, idx);
			if (check_deli(line, envi, idx, idx))
				start = idx + 1;
			else
				start = idx + 2;
			idx = start - 1;
		}
		idx++;
	}
	if (idx != 0)
		add_token(line, envi, start, idx);
}

void	quote_compare(t_envi *envi, char *str, char *tmp)
{
	int	tmp_idx;
	int	idx;

	idx = 0;
	tmp_idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] != '\'' && str[idx] != '\"')
			tmp[tmp_idx++] = str[idx];
		else if (envi->out_quote == '\0')
			envi->out_quote = str[idx];
		else if (envi->out_quote != str[idx])
			tmp[tmp_idx++] = str[idx];
		else if (envi->out_quote == str[idx])
			envi->out_quote = 0;
		idx++;
	}
	tmp[tmp_idx] = '\0';
}

void	remove_quote(t_envi *envi)
{
	t_token	*now;
	char	*tmp;

	now = envi->tokens;
	while (now != NULL && now->data != NULL)
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(now->data) + 1));
		if (!tmp)
			handle_error(-1);
		quote_compare(envi, now->data, tmp);
		change_data(now, tmp);
		now = now->next;
	}
}

void	parsing(char **envp, t_envi *envi, char *line)
{
	t_token	*token;
	t_token	*prev;

	setting(envi);
	tokenize(line, envi);
	token = envi->tokens;
	prev = NULL;
	while (token)
	{
		if (ft_strlen(token->data) == 0)
		{
			delete_token(envi, &token, &prev);
			continue ;
		}
		prev = token;
		token = token->next;
	}
	expand_var(envp, envi);
	remove_quote(envi);
	make_process(envi);
	free(line);
}
