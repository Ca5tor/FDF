SRCS =	get_next_line.c get_next_line_utils.c
	
OBJS 		= $(SRCS:.c=.o)

NAME 		= gnl.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

COMPILE		= $(CC) $(CFLAGS)

LIB			= ar rc $(NAME)

RM			= rm -f

RLIB		= ranlib

.PHONY:		all clean fclean re

all:		$(SRCS) $(NAME)

%.o: %.c get_next_line.h
	$(COMPILE) -c $< -o $@

$(NAME): $(OBJS)
	$(LIB) $(OBJS)
	$(RLIB) $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
