/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:32:58 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/26 21:26:04 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경 설정 관련 함수, 로직 중간에 또 쓰이는 부분이 있어 따로 빼주었습니다.
void	setting_etc(t_envi *envi)
{
	envi->quote[SINGLE] = 0;
	envi->quote[DOUBLE] = 0;
	envi->out_quote = NULL;
}

// 환경 설정 관련 함수2
void	setting(t_envi *envi)
{
	envi->tokens = (t_token *)malloc(sizeof(t_token));
	if (!(envi->tokens))
		exit(-1);
	envi->tokens->data = NULL;
	envi->tokens->next = NULL;
	envi->procs = (t_process *)malloc(sizeof(t_process));
	if (!(envi->procs))
		exit(-1);
	envi->procs->files = NULL;
	envi->procs->redirs = NULL;
	envi->procs->next = NULL;
	setting_etc(envi);
}

// 프로세스 구조체 테스트 출력용 함수입니다.
void print_processes(t_process *proc) {
    int idx = 0;
    while (proc != NULL && (proc->files != NULL || proc->redirs != NULL)) {
        printf("%d번째 프로세스\n", idx);

        // 파일 리스트 출력
        t_file *file = proc->files;
        printf("파일:\n");
        while (file != NULL) {
            printf("  %s\n", file->data);
            file = file->next;
        }

        // 리다이렉션 리스트 출력
        t_redir *redir = proc->redirs;
        printf("리다이렉션:\n");
        while (redir != NULL) {
            printf("  타입: %d, 데이터: %s\n", redir->type, redir->data);
            redir = redir->next;
        }

        // 다음 프로세스로 이동
        proc = proc->next;
        idx++;
    }
	if (idx == 0)
		printf("프로세스가 존재하지 않습니다.\n");
}

// envp변경을 위해서, envp 복사
char	**copy_envp(char **envp)
{
	int		len;
	int		idx;
	char	**cp_envp;

	if (!envp)
		return (0);
	len = ft_lstlen(envp);
	cp_envp = (char **)malloc(sizeof(char *) * (len + 1));
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
	cp_envp[idx] = 0;
	return (cp_envp);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**envp_cp;
	t_envi		*envi;

	(void)argv;
	if (argc != 1)
		handle_error(0);
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_sigusr2);
	envp_cp = copy_envp(envp);
	while (1)
	{
		line = readline("\033[34mminishell$>\033[0m ");
		if (!line)
			continue;
		add_history(line);
		envi = (t_envi *)malloc(sizeof(t_envi));
		if (!envi)
			handle_error(-1);
		parsing(envp_cp, envi, line);
		// print_processes(envi->procs);
		// printf("출력:\n");
		execute(envi, &envp_cp);
		free_envi(envi);
	}
	return (0);
}
