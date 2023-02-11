# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 20:17:58 by libacchu          #+#    #+#              #
#    Updated: 2023/02/11 12:42:38 by obibby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	car_demo
OBJ_DIR =	obj/
LIBMLX	=	./minilibx_linux/
SRC_DIR =	src/
SRC		=	main.c EasterEgg.c
INC		=	car.h EasterEgg.h
SYS		=	$(shell uname -s)
ifeq ($(SYS), Linux)
    LIBS    =    -Lminilibx_linux -lmlx -lXext -lX11 -lXrender
else
    LIBS    =    -Lminilibx_linux -lmlx -L/usr/X11/lib -lX11 -lXext -lXrender
endif
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		=	$(SRCS:%.c=$(OBJ_DIR)%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
DEFLT	=	\33[0m
RESET	=	\33[2K

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME) : $(OBJ) $(INC)
	@printf "\n"
	@make -C $(LIBMLX)
	@printf "$(RESET)\r$(GREY)Compiling $(BLUE)$(NAME)$(DEFLT)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(DEFLT)\n"
	@make clean -C $(LIBMLX)
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(DEFLT)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re