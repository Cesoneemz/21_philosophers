# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 18:49:51 by wlanette          #+#    #+#              #
#    Updated: 2022/05/18 20:29:12 by wlanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= ./srcs/ft_init.c ./srcs/ft_philo_actions.c ./srcs/ft_proceed.c \
				./srcs/ft_utils.c ./srcs/main.c
OBJS		= $(SRCS:.c=.o)

INCS		= ./includes/
INCS_HEADER	= ./includes/philo.h

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I$(INCS) -g -fsanitize=thread -ltsan -lpthread
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