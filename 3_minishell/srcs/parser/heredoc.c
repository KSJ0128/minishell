/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:59:20 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/06 17:50:33 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 치환
void	change_heredoc(char **line, char *key, char *val) // 원본 문자열, 환경변수 값, $ 위치, 치환할 문자열
{
	char	*tmp;
	int		idx;

	idx = 0;
	while ((*line)[idx] != '$')
		idx++;
	tmp = (char *)malloc(idx + 1);
	if (!tmp)
		handle_error(-1);
	ft_strlcpy(tmp, (*line), idx + 1);
	if (val)
		ft_strlcat(tmp, val, ft_strlen(tmp) + ft_strlen(val) + 1);
	idx++;
	idx += ft_strlen(key);
	ft_strlcat(tmp, (*line) + idx, ft_strlen(tmp) + ft_strlen((*line) + idx) + 1);
	free((*line));
	(*line) = tmp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;
	int					i;

	u_s1 = (const unsigned char *)s1;
	u_s2 = (const unsigned char *)s2;
	i = 0;
	while (u_s1[i] || u_s2[i])
	{
		if (u_s1[i] > u_s2[i])
			return (1);
		else if (u_s1[i] < u_s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*get_value(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '=')
		idx++;
	return (str + idx + 1);
}

char	*get_key(char *str, int code)
{
	int idx;
	int	len;
	char *key;

	idx = 0;
	if (code == 0)
	{
		while (str[idx] != '$')
			idx++;
		if (str[idx + 1] == '{')
			idx += 2;
		else
			idx++;
	}
	len = 0;
	while (str[idx + len] != '\0' && \
	(ft_isalnum(str[idx + len]) || str[idx + len] == '_'))
		len++;
	key = (char *)malloc(len + 1);
	if (!key)
		handle_error(-1);
	ft_strlcpy(key, str + idx, len + 1);
	return (key);
}

// envp 내에서 변환 가능한 환경변수 있는지 탐색
char	*can_change_heredoc(char **envp, char *key)
{
	char	**ptr;
	char	*var;
	char	*env_key;

	if (!key || key[0] == '\0')
		return (NULL);
	ptr = envp;
	while (*ptr != NULL)
	{
		var = *ptr;
		env_key = get_key(var, 1);
		if (!env_key || env_key[0] == '\0')
			return (NULL);
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
		value = NULL;
		if (str[idx] == '$')
		{
			key = get_key(str, 0);
			value = can_change_heredoc(envp, key);
			change_heredoc(line, key, value);
		}
		idx++;
	}
}
