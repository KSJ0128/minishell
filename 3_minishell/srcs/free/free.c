/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:54:32 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/18 21:42:01 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 토큰 데이터 교체
void	change_data(t_token *token, char *str)
{
	free(token->data);
	token->data = str;
}

// 토큰 리스트 free
void	free_tokens(t_token *tokens)
{
	t_token *now;
	t_token *tmp;

	now = tokens;
	while (now != NULL)
	{
		free(now->data);
		tmp = now;
		now = now->next;
		free(tmp);
	}
}

// 프로세스 구조체 free
void	free_proc(t_process *proc)
{
	t_file	*file;
	t_redir	*redir;
	t_file	*tmpf;
	t_redir	*tmpr;

	file = proc->files;
	while (file != NULL)
	{
		free(file->data);
		tmpf = file;
		file = file->next;
		free(tmpf);
	}
	redir = proc->redirs;
	while (redir != NULL)
	{
		free(redir->data);
		tmpr = redir;
		redir = redir->next;
		free(tmpr);
	}
}

// 프로세스 구조체 리스트 free
void	free_procs(t_process *procs)
{
	t_process *now;
	void	*tmp;

	now = procs;
	while (now != NULL)
	{
		free_proc(now);
		tmp = now;
		now = now->next;
		free(tmp);
	}
}

// 설정 관련 구조체 envi free
void	free_envi(t_envi *envi)
{
	free_tokens(envi->tokens);
	free_procs(envi->procs);
	free(envi);
}
