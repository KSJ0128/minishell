/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:33:42 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/28 15:33:28 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 1
# define NULL 0
# define TRUE 1
# define FALSE 0

# define SINGLE 0
# define DOUBLE 1

# define DELI_REDIR 0
# define DELI_ETC 1

// 리다이렉션 플래그
# define REDIR_O 1 // >
# define REDIR_I 2 // <
# define REDIR_AO 3 // >>
# define REDIR_H 4 // <<

# define ERROR_QUOTE 0

# define BUFFER_SIZE 5 // get_next_line

# include <stdio.h>
# include "libft.h"
# include <signal.h> // signal, kill 사용을 웨해 추가
# include <fcntl.h> // open 함수 사용을 위해 추가

//노트북
// #include "readline/readline.h"
// #include "readline/history.h"

//클러스터
# include "readline.h"
# include "history.h"

// 프로세스 구조체에 담기 전 토큰 리스트
typedef struct token
{
	char	*data;
	struct token	*next;
}	t_token;

// 프로세스 구조체 - 파일 리스트
typedef struct file
{
	void	*next;
	char	*data;
}	t_file;

// 프로세스 구조체 - 리다이렉션 리스트
typedef struct redir
{
	void	*next;
	int		type;
	char	*data;
}	t_redir;

// 프로세스 구조체
typedef struct process
{
	t_file		*files;
	t_redir		*redirs;
	void		*next;
}	t_process;

// 로직에 사용할 변수, 설정 관련 구조체
typedef struct envi
{
	t_token	*tokens; // 토큰 리스트
	t_process	*procs; // 프로세스 구조체 리스트
	int		quote[2]; // 토큰 분리시 따옴표 체크
	char	out_quote; // 환경 변수 변환시 외부 따옴표가 무엇인지 체크
}	t_envi;

// error.c
void	handle_error(int num);

// free.c
void	change_data(t_token *token, char *str);
void	free_tokens(t_token *tokens);
void	free_proc(t_process *proc);
void	free_procs(t_process *procs);
void	free_envi(t_envi *envi);

// syntax_check.c
int		check_quote(char *line, t_envi *envi);
int		is_quote(char c, t_envi *envi);
int		is_deli(char *line, t_envi *envi, int idx);
int		check_deli(char *line, t_envi *envi, int start, int idx);

// parsing.c
void	add_token(char *line, t_envi *envi, int start, int idx);
void	tokenize(char *line, t_envi *envi);
void	remove_quote(t_envi *envi);
void	parsing(char **envp, t_envi *envi, char *str);

// expand.c
void	set_out_quote(char quote, t_envi *envi);
void	change_var(t_token *token, char *var, int d_idx, int s_idx);
void	can_change_var(char **envp, t_token *token, char *str, int d_idx);
void	expand_var(char **envp, t_envi *envi);

// process.c
int		redir_check(t_token *token);
void	push_file(t_token *token, t_process *proc);
void	push_redir(t_token *token, t_process *proc);
void	push_proc(t_process *proc);
void	make_process(t_envi *envi);

// main.c
void	setting_etc(t_envi *envi);
void	setting(t_envi *envi);

/*****************************************************/
/* execute */
// execute.c
void	execute(t_envi	*envi, char ***envp);

// path.c
void	ft_execve(t_process *proc, char **envp);

// redirect.c
void	ft_redirect(t_redir *redir);

/* builtin */ // 오류 처리를 어떻게 해야할 지 모르겠음
int		ft_echo(t_file *file);
int		ft_pwd(void);
void	ft_cd(t_file *file);
void	ft_export(t_file *file, char ***envp);
void	ft_env(char **envp);
void	ft_unset(char ***envp, t_file *file);
void	ft_exit(t_file *file);

// builtin.c
int		ck_is_builtin(t_process *proc);
void	exec_builtin(t_process *proc, char ***envp);

// ft_export.c
int		find_str(char *en, char *str);

// handle_lst.c
int		ft_lstlen(char **lst);
void	free_lst(char **lst);
int		proc_len(t_process *proc);
int		ft_filelen(t_file *file);
char	**mk_arg(t_process *proc, char *cmd_path);

// handle_signal.c
void	handle_sigusr1(int sig);
void	handle_sigusr2(int sig);

/* get_next_line */
// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
int		ft_strchr_num(const char *s, int c, int *bk_idx);

#endif
