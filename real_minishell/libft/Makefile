NAME = libft.a

CC = gcc
CFLAG = -Wall -Wextra -Werror
ARC = ar -rc
RM = rm -f

FT_C = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_toupper.c ft_split.c ft_strcmp.c

FT_O = $(FT_C:.c=.o)

BONUS_C = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

BONUS_O = $(BONUS_C:.c=.o)

FT_H = libft.h

ifdef BONUS
	OBJS = $(FT_O) $(BONUS_O)
else
	OBJS = $(FT_O)
endif

all : $(NAME)

bonus :
	make BONUS=1

$(NAME) : $(OBJS)
	$(ARC) $@ $^

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(FT_H)

clean :
	$(RM) $(FT_O) $(BONUS_O)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re