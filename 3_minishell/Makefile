NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

LFLAGS = -lreadline -L./$(LIBFT_DIR) -lft
INCLUDES = -I./incs -I./libft -I/usr/local/include/readline

LIBFT_DIR = libft
LIBFT = ./$(LIBFT_DIR)/libft.a

SRCS = builtin/builtin.c builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c \
error/error_handler.c execute/execute.c execute/exit.c execute/path.c execute/redirect_one.c execute/redirect.c free/free.c get_next_line/get_next_line_utils.c \
get_next_line/get_next_line.c parse/expand.c parse/parsing_heredoc.c parse/parsing.c parse/synctax_check.c parse/process.c utils/expand_util.c utils/handle_fd.c utils/handle_free.c \
utils/handle_lst.c utils/handle_signal.c utils/heredoc_util.c main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LFLAGS)

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean;
	@$(RM) $(OBJS)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean;
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
