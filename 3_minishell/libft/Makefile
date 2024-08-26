# target file
NAME = libft.a

# compile options
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
AR = ar -rc
RM = rm -f

# include directories
INCLUDES = -I./incs

# source files
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS := $(shell find $(SRCS_DIR) -type f -name '*.c')
OBJS := $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

DEPS := $(OBJS:.o=.d)

# build the library
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

# handle dependencies
-include $(DEPS)

# clean up object files and dependency files
clean:
	$(RM) $(OBJS) $(DEPS)

# clean up all, including the library
fclean: clean
	$(RM) $(NAME)

# rebuild the library
re: fclean all

# phony targets
.PHONY: all clean fclean re bonus
