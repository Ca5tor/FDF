# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 13:20:23 by ltacos            #+#    #+#              #
#    Updated: 2022/02/28 13:38:21 by ltacos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -g

GNL					=	$(GNL_DIRECTORY)gnl.a
GNL_DIRECTORY 		=	 ./utils/GNL/

LIBFT 				=	$(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY 	=	./utils/LIBFT/

MINILIBX 			=	$(MINILIBX_DIRECTORY)libmlx_Linux.a
MINILIBX_DIRECTORY	=	./mlx/
MLX_FLAGS 			=	-lm -lmlx -lX11 -lXext

HEADER		=	src/fdf.h \
				mlx/mlx.h \
				utils/LIBFT/libft.h \
				utils/GNL/get_next_line.h

SOURCES_L	=	get_map.c \
				key_utils.c \
				main.c \
				map_utils.c \
				print_map.c \
				projection.c \
				struct_init.c \
				utils.c
	
SOURCES_DIRECTORY	= ./src/
SOURCES 			= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_L))
OBJECTS_DIRECTORY 	= objects/
OBJECTS_LIST 		= $(patsubst %.c, %.o, $(SOURCES_L))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re test norm

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) 
	@make -C $(LIBFT_DIRECTORY)
	@make -C $(GNL_DIRECTORY)
	@make -C $(MINILIBX_DIRECTORY)
	@$(CC) $(FLAGS) $(OBJECTS) $(GNL) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER)
	@mkdir -p $(OBJECTS_DIRECTORY)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -sC $(LIBFT_DIRECTORY) clean
	@make -sC $(GNL_DIRECTORY) clean
	@make -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	@rm -f $(MINILIBX)
	@rm -f $(LIBFT)
	@rm -f $(GNL)
	@rm -f $(NAME)

re:	fclean all 

test:	all
		./fdf 42.fdf

norm:
	@norminette src/ utils/
