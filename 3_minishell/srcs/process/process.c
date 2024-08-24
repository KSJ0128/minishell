/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:13:47 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/24 15:37:56 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 리다이렉션 플래그 체크
int	redir_check(t_token *token)
{
	if (ft_strncmp(token->data, ">", ft_strlen(token->data)) == 0)
		return (REDIR_O);
	else if (ft_strncmp(token->data, "<", ft_strlen(token->data)) == 0)
		return (REDIR_I);
	else if (ft_strncmp(token->data, ">>", ft_strlen(token->data)) == 0)
		return (REDIR_AO);
	else if (ft_strncmp(token->data, "<<", ft_strlen(token->data)) == 0)
		return (REDIR_H);
	return (FALSE);
}

// 파일 리스트에 파일 추가
void	push_file(t_token *token, t_process *proc)
{
	t_process *now;
	t_file *last;
	t_file *file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		handle_error(-1);
	file->data = ft_strdup(token->data);
	file->next = NULL;
	now = proc;
	while (now->next != NULL)
		now = now->next;
	last = now->files;
	if (last == NULL)
		now->files = file;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = file;
	}
}

// 리다이렉션 리스트에 리다이렉션 추가
void	push_redir(t_token *token, t_process *proc)
{
	t_process *now;
	t_redir *redir;
	t_redir *last;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		handle_error(-1);
	redir->type = redir_check(token);
	token = token->next;
	if (token == NULL)
		redir->data = NULL;
	else
		redir->data = ft_strdup(token->data);
	redir->next = NULL;
	now = proc;
	while (now->next != NULL)
		now = now->next;
	last = now->redirs;
	if (last == NULL)
		now->redirs = redir;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = redir;
	}
}

// 프로세스 리스트에 프로세스 추가
void	push_proc(t_process *proc)
{
	t_process *now;
	t_process *new;

	now = proc;
	new = (t_process *)malloc(sizeof(t_process));
	if (!new)
		handle_error(-1);
	new->files = NULL;
	new->redirs = NULL;
	new->next = NULL;
	while (now->next != NULL)
		now = now->next;
	now->next = new;
	now = now->next;
}

// 프로세스 구조체 리스트 생성
void	make_process(t_envi *envi)
{
	t_token		*now;
	t_process	*proc;

	now = envi->tokens;
	proc = envi->procs;
	while (now != NULL && now->data != NULL)
	{
		if (ft_strncmp(now->data, "|", ft_strlen(now->data)) == 0)
			push_proc(proc);
		else if (!redir_check(now))
			push_file(now, proc);
		else
		{
			push_redir(now, proc);
			now = now->next;
		}
		if (now == NULL)
			return ;
		now = now->next;
	}
}
