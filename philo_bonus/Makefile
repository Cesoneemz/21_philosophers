# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 18:49:51 by wlanette          #+#    #+#              #
#    Updated: 2022/05/21 02:32:08 by wlanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus
SRCS		= ./srcs/ft_init.c ./srcs/ft_philo_actions.c ./srcs/ft_proceed.c \
				./srcs/ft_utils.c ./srcs/main.c ./srcs/ft_philo_eat.c \
				./srcs/ft_optimization.c
OBJS		= $(SRCS:.c=.o)

INCS		= ./includes/
INCS_HEADER	= ./includes/philo.h

CC			= clang
CFLAGS		= -Wall -Werror -Wextra -I$(INCS) -g 
RM			= rm -rf

all:		$(NAME)

$(NAME):	$(OBJS) $(INCS_HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re