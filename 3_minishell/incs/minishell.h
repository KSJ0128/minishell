/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:33:42 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/05 20:40:07 by seungbel         ###   ########.fr       */
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
# include <termios.h> // terminal 설정제어(SIGINT, SIGQUIT)
#include <sys/ioctl.h> // heredoc_handler

extern int	global_sig;

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
void	send_errmsg(char *cmd, int exitcode);
int		send_errmsg_export(char *cmd, int code);

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
void	quote_compare(t_envi *envi, char *str, char *tmp);
void	remove_quote(t_envi *envi);
void	parsing(char **envp, t_envi *envi, char *str);

// expand.c
void	change_var(t_token *token, char *var, int d_idx, int s_idx);
void	remove_var(t_token *token, int d_idx);
void	can_change_var(char **envp, t_token *token, char *str, int d_idx);
int		is_special_var(t_token *now, int idx, char c);
void	set_out_quote(char quote, t_envi *envi);
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
void	ft_redirect(t_redir *redir, t_file *file);
void	here_doc(char *del, t_file *file);
int		except_heredoc_one(t_redir *redir);
int		ft_redirect_one(t_redir *redir, t_file *file);

/* builtin */ // 오류 처리를 어떻게 해야할 지 모르겠음
int		ft_echo(t_file *file);
int		ft_pwd(void);
int		ft_cd(t_file *file);
int		ft_export(t_file *file, char ***envp);
int		ft_env(char **envp);
int		ft_unset(char ***envp, t_file *file);
void	ft_exit(t_file *file); // 진짜 끝내는 거니까 상관없지 않나?

// builtin.c
int		ck_is_builtin(t_process *proc);
int		exec_builtin(t_process *proc, char ***envp);
int		ck_export_valid(char *name);

// ft_export.c
int		find_str(char *en, char *str);
int		join_envp(char ***envp, char *str);

// handle_lst.c
int		ft_lstlen(char **lst);
void	free_lst(char **lst);
int		proc_len(t_process *proc);
int		ft_filelen(t_file *file);
char	**mk_arg(t_process *proc, char *cmd_path);

// handle_signal.c
void	handle_signal(int sig);
void	handle_signal2(int sig);
void	handle_signal3(int sig);
void	init_sig_termi(void);
void	reset_sig_termi(void);

// handle_fd.c
void	dup_all(int (*dup_fd)[3]);
int		dup2_all(int (*dup_fd)[3], int stat);

/* get_next_line */
// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
int		ft_strchr_num(const char *s, int c, int *bk_idx);

// exit.c
int		get_exitcode(pid_t last, int proc_num); // signal 추가 해주기
void	record_exitcode(int code, char ***envp);
#endif
