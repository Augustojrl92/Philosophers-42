# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 12:39:32 by aurodrig          #+#    #+#              #
#    Updated: 2024/11/15 16:39:25 by aurodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g3 #-fsanitize=thread 

RM = rm -rf


SRCS = 	src_bonus/philo_bonus.c \
		src_bonus/init_utils_bonus.c \
		src_bonus/delay_utils_bonus.c \
		src_bonus/aux1_bonus.c \

	
		

		
OBJ =  $(SRCS:.c=.o)


CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(NAME) : $(OBJ)
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	gcc $(CFLAGS)  $(OBJ) -o $(NAME)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(NAME)
	$(RM) $(OBJ)

re : fclean all


.PHONY:     all clean fclean re