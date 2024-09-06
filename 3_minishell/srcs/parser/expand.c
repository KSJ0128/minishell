/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:36:17 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/04 17:05:30 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 치환
void	change_var(t_token *token, char *var, int d_idx, int v_idx)
{
	char	*str;
	char	*tmp;
	int		len;

	str = token->data;
	if (str[d_idx + 1] == '{' && str[v_idx] == '}') // $ 뒤에 중괄호가 오고, 변수명 뒤에 바로 }가 오는 경우
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

// 존재하지 않는 환경 변수 처리
void	remove_var(t_token *token, int d_idx)
{
	int		d_len;
	char	*str;
	char	*src;

	d_len = 0;
	str = token->data + d_idx + 1;
	while (str[d_len] != '\0' && (ft_isalnum(str[d_len]) || str[d_len] == '_'))
		d_len++;
	src = token->data + d_idx + d_len + 1; // 잘라내려는 부분의 시작 위치
	ft_memmove(str - 1, src, ft_strlen(src) + 1); // src를 $ 위치에 덮어씀
}

// envp 내에서 변환 가능한 환경변수 있는지 탐색
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
		if (var[idx] == '=' && !ft_isalnum(str[idx]) && str[idx] != '_') // 환경변수는 =를 만나고 str은 변수명으로 올 수 없는 문자를 만나는 경우
		{
			if (token->data[d_idx + 1] == str[0]) // $ 뒤에 중괄호가 오는지에 따라 인덱스 다르게 넘겨줌
				return (change_var(token, var + idx + 1, d_idx, d_idx + idx + 1));
			else
				return (change_var(token, var + idx + 1, d_idx, d_idx + idx + 2));
		}
		ptr++;
	}
	return (remove_var(token, d_idx));
}

// $ 관련 특수문자 체크
int	is_special_var(t_token *now, int idx, char c)
{
	if (c == '$') // 현재 프로세스의 pid
	{
		change_var(now, ft_itoa(getpid()), idx, idx + 2);
		return (TRUE);
	}
	else if (c == '0') // 현재 실행 중인 스크립트의 이름을 반환
		return (TRUE);
	else if (c == '!') // 마지막으로 실행된 백그라운드 작업의 프로세스 ID를 반환
		return (TRUE);
	else if (c == '(')
		return (TRUE);
	// 이외에도 처리값 어떻게 할지 고민해봐야할 듯
	else
		return (FALSE);
}

// 환경변수 관련 따옴표 플래그 체크
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

// 토큰별 환경변수 확장
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
			if (is_quote(now->data[idx], envi)) // 따옴표 만났을 때 가장 바깥 따옴표 정보 갱신
				set_out_quote(now->data[idx], envi);
			else if (now->data[idx] == '$' && envi->out_quote != '\'') // $ 만나고, 외부 따옴표가 '가 아닌 경우
			{
				if (!is_special_var(now, idx, now->data[idx + 1])) // $ 뒤에 의미 가지는 특별한 문자 오는 경우
					can_change_var(envp, now, now->data + idx + 1, idx);
			}
			idx++;
		}
		now = now->next;
	}
}
