/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:49:32 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/08 16:20:55 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_heredoc(char **line, int d_idx, char *key, char *val)
{
	char	*tmp;
	char	*str;
	int		idx;

	str = *line + d_idx;
	idx = 1;
	while (ft_isalnum(str[idx]) || str[idx] == '_' || str[idx] == '?')
		idx++;
	if (idx == 1 && str[idx] == '$')
		idx++;
	tmp = (char *)malloc(d_idx + ft_strlen(val) + ft_strlen(str + idx) + 1);
	if (!tmp)
		handle_error(-1);
	ft_strlcpy(tmp, *line, d_idx + 1);
	ft_strlcat(tmp, val, ft_strlen(tmp) + ft_strlen(val) + 1);
	ft_strlcat(tmp, str + idx, ft_strlen(tmp) + ft_strlen(str + idx) + 1);
	free((*line));
	(*line) = tmp;
	free(key);
}

void	remove_heredoc(char **line, int d_idx, char *key)
{
	char	*str;
	char	*tmp;
	int		idx;

	str = *line + d_idx;
	idx = 1;
	while (ft_isalnum(str[idx]) || str[idx] == '_')
		idx++;
	tmp = str + idx;
	ft_memmove(str, tmp, ft_strlen(tmp) + 1);
	free(key);
}

char	*can_change_heredoc(char **envp, char *key)
{
	char	**ptr;
	char	*var;
	char	*env_key;

	if (!key || key[0] == '\0')
		return (NULL);
	if (ft_strcmp(key, "$") == 0)
		return (ft_itoa(getpid()));
	ptr = envp;
	while (*ptr != NULL)
	{
		var = *ptr;
		env_key = get_key(var);
		if (ft_strcmp(key, env_key) == 0)
		{
			free(env_key);
			return (get_value(var));
		}
		free(env_key);
		ptr++;
	}
	return (NULL);
}

void	expand_heredoc(char **envp, char **line)
{
	int		idx;
	char	*str;
	char	*key;
	char	*value;

	idx = 0;
	str = *line;
	while (str != NULL && str[idx] != '\0')
	{
		if (str[idx] == '$')
		{
			key = get_key(str + idx + 1);
			value = can_change_heredoc(envp, key);
			if (key && !value)
				remove_heredoc(line, idx, key);
			else if (key && value)
				change_heredoc(line, idx, key, value);
			str = *line;
			if (key && ft_strcmp(key, "$") == 0)
				free(value);
		}
		idx++;
	}
}
