/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:36:17 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/09 18:05:16 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_var(t_token *token, char *var, int d_idx, int v_idx)
{
	char	*str;
	char	*tmp;
	int		len;

	str = token->data;
	if (str[d_idx + 1] == '{' && str[v_idx] == '}')
		v_idx++;
	len = d_idx + ft_strlen(var) + ft_strlen(str + v_idx);
	tmp = (char *)malloc(len + 1);
	if (!tmp)
		handle_error(-1);
	ft_strlcpy(tmp, str, d_idx + 1);
	ft_strlcat(tmp, var, ft_strlen(tmp) + ft_strlen(var) + 1);
	ft_strlcat(tmp, str + v_idx, ft_strlen(tmp) + ft_strlen(str + v_idx) + 1);
	change_data(token, tmp);
}

void	remove_var(t_token *token, int d_idx)
{
	int		d_len;
	char	*str;
	char	*src;

	d_len = 0;
	str = token->data + d_idx + 1;
	while (str[d_len] != '\0' && (ft_isalnum(str[d_len]) || str[d_len] == '_'))
		d_len++;
	src = token->data + d_idx + d_len + 1;
	ft_memmove(str - 1, src, ft_strlen(src) + 1);
}

void	can_change_var(char **envp, t_token *token, char *str, int d_idx)
{
	char	**ptr;
	char	*var;
	int		idx;

	ptr = envp;
	while (*ptr != NULL)
	{
		var = *ptr;
		idx = 0;
		if (str[0] == '{')
			str++;
		while (var[idx] == str[idx] && var[idx] != '=' && str[idx] != '\0')
			idx++;
		if (var[idx] == '=' && !ft_isalnum(str[idx]) && str[idx] != '_')
		{
			if (token->data[d_idx + 1] == str[0])
				return (change_var(token, var + idx + 1, \
				d_idx, d_idx + idx + 1));
			else
				return (change_var(token, var + idx + 1, \
				d_idx, d_idx + idx + 2));
		}
		ptr++;
	}
	return (remove_var(token, d_idx));
}

void	expand_var(char **envp, t_envi *envi)
{
	t_token	*now;
	int		idx;

	now = envi->tokens;
	while (now != NULL && now->data != NULL)
	{
		idx = 0;
		while (now->data[idx] != '\0')
		{
			if (is_quote(now->data[idx], envi))
				set_out_quote(now->data[idx], envi);
			else if (now->data[idx] == '$' && envi->out_quote != '\'')
			{
				if (!ft_isalnum(now->data[idx + 1]) \
				&& now->data[idx + 1] != '_' && now->data[idx + 1] != '?' \
				&& now->data[idx + 1] != '$')
					break ;
				if (!is_special_var(now, idx, now->data[idx + 1]))
					can_change_var(envp, now, now->data + idx + 1, idx);
			}
			idx++;
		}
		now = now->next;
	}
}
