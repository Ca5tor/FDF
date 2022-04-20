SRCS 		=	ft_atoi.c   ft_putstr_fd.c	\
				ft_split.c  ft_strdup.c		\
				ft_strlen.c ft_substr.c		\
				ft_strchr.c ft_strnstr.c	\
				ft_bzero.c
	
OBJS 		= $(SRCS:.c=.o)

NAME 		= libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

COMPILE		= $(CC) $(CFLAGS)

LIB			= ar rc $(NAME)

RM			= rm -f

RLIB		= ranlib

.PHONY:		all clean fclean re

all:		$(SRCS) $(NAME)

%.o: %.c libft.h
	$(COMPILE) -c $< -o $@

$(NAME): $(OBJS)
	$(LIB) $(OBJS)
	$(RLIB) $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
