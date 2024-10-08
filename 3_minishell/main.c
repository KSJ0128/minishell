/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:32:58 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/09 13:21:44 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	setting_etc(t_envi *envi)
{
	envi->quote[SINGLE] = 0;
	envi->quote[DOUBLE] = 0;
	envi->out_quote = 0;
}

void	setting(t_envi *envi)
{
	envi->tokens = (t_token *)malloc(sizeof(t_token));
	if (!(envi->tokens))
		exit(-1);
	envi->tokens->data = 0;
	envi->tokens->next = 0;
	envi->procs = (t_process *)malloc(sizeof(t_process));
	if (!(envi->procs))
		exit(-1);
	envi->procs->files = 0;
	envi->procs->redirs = 0;
	envi->procs->next = 0;
	setting_etc(envi);
}

char	**copy_envp(char **envp)
{
	int		len;
	int		idx;
	char	**cp_envp;

	if (!envp)
		return (0);
	len = ft_lstlen(envp);
	cp_envp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!cp_envp)
		handle_error(-1);
	idx = 0;
	while (idx < len)
	{
		cp_envp[idx] = ft_strdup(envp[idx]);
		if (!cp_envp[idx])
			handle_error(-1);
		idx++;
	}
	cp_envp[idx] = ft_strdup("?=0");
	if (!cp_envp[idx])
		handle_error(-1);
	cp_envp[++idx] = 0;
	return (cp_envp);
}

int	ck_line(char *line)
{
	int	idx;

	if (!line)
	{
		printf("\033[1A\033[12Cexit\n");
		exit(0);
	}
	idx = 0;
	if (!(*line))
	{
		free(line);
		line = 0;
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	char				**envp_cp;
	t_envi				*envi;

	(void)argv;
	if (argc != 1)
		handle_error(0);
	envp_cp = copy_envp(envp);
	while (1)
	{
		init_sig_termi();
		line = readline("\033[34mminishell$>\033[0m ");
		if (!ck_line(line))
			continue ;
		add_history(line);
		envi = (t_envi *)malloc(sizeof(t_envi));
		if (!envi)
			handle_error(-1);
		if (g_sig == 2)
			record_exitcode(1, &envp_cp);
		parsing(envp_cp, envi, line);
		execute(envi, &envp_cp);
	}
	free_lst(&envp_cp);
	return (0);
}
