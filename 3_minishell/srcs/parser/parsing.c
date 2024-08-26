/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:07:27 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/24 15:37:47 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// start ~ idx - 1까지의 토큰 추가
void	add_token(char *line, t_envi *envi, int start, int idx)
{
	t_token	*now;
	t_token	*token;
	char	*str;

	str = ft_strndup(line + start, idx - start);
	if (!str)
		handle_error(-1);
	now = envi->tokens;
	if (now->data == NULL)
		now->data = str;
	else
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (!token)
			handle_error(-1);
		token->data = str;
		token->next = NULL;
		while (now->next != NULL)
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
		if (line[idx] == '\'' || line[idx] == '\"') // 따옴표 내, 외부 플래그 설정
			is_quote(line[idx], envi);
		else if (is_deli(line, envi, idx))
		{
			if (start < idx) // 구분자 앞에 문자열 존재시 토큰 추가
				add_token(line, envi, start, idx);
			if (check_deli(line, envi, idx, idx)) // 구분자 종류에 따라 인덱스 증가 다르게
				start = idx + 1;
			else
				start = idx + 2;
			idx = start - 1;
		}
		idx++;
	}
	if (idx != 0)
		add_token(line, envi, start, idx); // 널 문자 만났을 때 토큰 추가
}

// 토큰 내 따옴표 제거
void	remove_quote(t_envi *envi)
{
	t_token *now;
	char	*str;
	char	*tmp;
	int		tmp_idx;
	int		idx;

	now = envi->tokens;
	while (now != NULL && now->data != NULL)
	{
		str = now->data;
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!tmp)
			handle_error(-1);
		idx = 0;
		tmp_idx = 0;
		while (str[idx] != '\0')
		{
			if (str[idx] != '\'' && str[idx] != '\"') // 따옴표 제외하고 새 문자열 생성
				tmp[tmp_idx++] = str[idx];
			idx++;
		}
		tmp[tmp_idx] = '\0';
		change_data(now, tmp); // 토큰 데이터 교체
		now = now->next;
	}
}

void	parsing(char **envp, t_envi *envi, char *line)
{
	setting(envi);
	if (!check_quote(line, envi)) // 따옴표 쌍 체크
		handle_error(1);
	tokenize(line, envi); // 유저 입력 구분자 기준으로 토크나이즈(화이트 스페이스, |, 리다이렉션)
	expand_var(envp, envi); // 환경변수 확장
	remove_quote(envi); // 따옴표 제거
	make_process(envi); // 프로세스 구조체 리스트 생성
}
