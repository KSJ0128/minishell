/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:33:42 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/08 16:45:31 by seojkim          ###   ########.fr       */
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

# define REDIR_O 1
# define REDIR_I 2
# define REDIR_AO 3
# define REDIR_H 4

# define ERROR_QUOTE 0

# define BUFFER_SIZE 5

# include <stdio.h>
# include "libft.h"
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include "readline.h"
# include "history.h"

extern int	g_global_sig;

typedef struct token
{
	char			*data;
	struct token	*next;
}	t_token;

typedef struct file
{
	void	*next;
	char	*data;
}	t_file;

typedef struct redir
{
	void	*next;
	int		type;
	char	*data;
}	t_redir;

typedef struct process
{
	t_file		*files;
	t_redir		*redirs;
	void		*next;
}	t_process;

typedef struct envi
{
	t_token		*tokens;
	t_process	*procs;
	int			quote[2];
	char		out_quote;
}	t_envi;

void	handle_error(int num);
void	send_errmsg(char *cmd, char *msg, int exitcode);
int		send_errmsg_in(char *cmd, char *msg, int code);

void	change_data(t_token *token, char *str);
void	free_tokens(t_token *tokens);
void	free_proc(t_process *proc);
void	free_procs(t_process *procs);
void	free_envi(t_envi *envi);

int		check_quote(char *line, t_envi *envi);
int		is_quote(char c, t_envi *envi);
int		is_deli(char *line, t_envi *envi, int idx);
int		check_deli(char *line, t_envi *envi, int start, int idx);

void	add_token(char *line, t_envi *envi, int start, int idx);
void	tokenize(char *line, t_envi *envi);
void	quote_compare(t_envi *envi, char *str, char *tmp);
void	remove_quote(t_envi *envi);
void	parsing(char **envp, t_envi *envi, char *str);

void	change_heredoc(char **line, int idx, char *key, char *val);
void	remove_heredoc(char **line, int idx, char *key);
char	*can_change_heredoc(char **envp, char *key);
void	expand_heredoc(char **envp, char **line);

char	*get_key(char *str);
char	*get_value(char *str);

void	change_var(t_token *token, char *var, int d_idx, int s_idx);
void	remove_var(t_token *token, int d_idx);
void	can_change_var(char **envp, t_token *token, char *str, int d_idx);
void	expand_var(char **envp, t_envi *envi);

int		is_special_var(t_token *now, int idx, char c);
void	set_out_quote(char quote, t_envi *envi);

int		redir_check(t_token *token);
void	push_file(t_token *token, t_process *proc);
void	push_redir(t_token *token, t_process *proc);
void	push_proc(t_process *proc);
void	make_process(t_envi *envi);

void	setting_etc(t_envi *envi);
void	setting(t_envi *envi);
char	**copy_envp(char **envp);
int		ck_line(char *line);

void	execute(t_envi	*envi, char ***envp);

void	ft_execve(t_process *proc, char **envp);
char	**mk_arg(t_process *proc, char *cmd_path);
char	*find_path(char *cmd, char **envp);
char	*mk_cmdpath(char *cmd, char *path);
char	*path_pointer(char **envp);

void	ft_redirect(t_redir *redir, t_file *file, char **join_envp);
void	here_doc(char *del, t_file *file, char **envp);
int		except_heredoc_one(t_redir *redir);
int		ft_redirect_one(t_redir *redir, t_file *file, char **envp);

int		ft_echo(t_file *file);
int		ft_pwd(void);
int		ft_cd(t_file *file, char ***envp);
int		ft_export(t_file *file, char ***envp);
int		ft_env(char **envp);
int		ft_unset(char ***envp, t_file *file);
void	ft_exit(t_file *file);

int		ck_is_builtin(t_process *proc);
int		exec_builtin(t_process *proc, char ***envp);
int		ck_export_valid(char *name);

int		find_str(char *en, char *str);
int		join_envp(char ***envp, char *str);

int		ft_lstlen(char **lst);
int		proc_len(t_process *proc);
int		ft_filelen(t_file *file);

void	handle_signal(int sig);
void	handle_signal2(int sig);
void	handle_signal3(int sig);
void	init_sig_termi(void);
void	reset_sig_termi(void);

void	dup_all(int (*dup_fd)[3]);
int		dup2_all(int (*dup_fd)[3], int stat);

void	free_str(char **str);
void	free_lst(char ***lst);
void	free_arg(int idx, char ***arg);

char	*get_next_line(int fd);

int		ft_strchr_num(const char *s, int c, int *bk_idx);

int		get_exitcode(pid_t last, int proc_num);
void	record_exitcode(int code, char ***envp);
#endif
