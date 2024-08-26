MINISHELL = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

## 노트북
# LFLAGS = -L./$(LIBFT_DIR) -lft -L/opt/homebrew/Cellar/readline/8.2.10/lib -lreadline
# INCLUDES = -I./incs -I./libft/incs -I/opt/homebrew/Cellar/readline/8.2.10/include/readline

## 클러스터
LFLAGS = -lreadline -L./$(LIBFT_DIR) -lft
INCLUDES = -I./incs -I./libft/incs -I/usr/local/include/readline

LIBFT_DIR = libft
LIBFT = ./$(LIBFT_DIR)/libft.a

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.c')

OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

DEPS := $(OBJS:%.o=%.d)

all : $(MINISHELL)

$(MINISHELL) : $(OBJS) $(LIBFT)
	$(CC) -o $@ $^ $(INCLUDES) $(LFLAGS)

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

-include $(DEPS)

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean;
	@$(RM) $(OBJS) $(DEPS)
	@rmdir -p $(OBJS_DIR) || true

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean;
	$(RM) $(MINISHELL)

re : fclean all

.PHONY : all clean fclean re
