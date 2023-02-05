# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/02/04 23:36:52 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	car_demo
OBJ_DIR =	obj/
LIBMLX	=	./minilibx_linux/
SRC_DIR =	src/
SRC		=	main.c
INC		=	car.h
SYS		=	$(shell uname -s)
# ifeq ($(SYS), Linux)
#     LIBS    =    -Lminilibx_linux -lm -lmlx -lXext -lX11
# endif
# ifeq ($(SYS), Darwin)
#     LIBS    =    -L/usr/X11/lib -lX11 -lXext ./minilibx_linux/libmlx.a
# endif
LIBS    =    -Lminilibx_linux -lm -lmlx -lXext -lX11 -lXrender
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
RESET	=	\33[0m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $(INC)
	@printf "\n"
	@make -C $(LIBMLX)
#	@cp ./minilibx_mms/libmlx.dylib .
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(RESET)\n"
	@make clean -C $(LIBMLX)
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(RESET)\n"
#	@rm libmlx.dylib
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re