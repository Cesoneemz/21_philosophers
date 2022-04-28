/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:53:31 by wlanette          #+#    #+#             */
/*   Updated: 2022/04/28 20:55:27 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				count_eat;
	long long		last_eat_time;
	struct s_config	*config;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_config
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				philo_is_die;
	int				philo_is_ate;
	long long		timestamp;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	mutex_writing;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_condition;
}				t_config;

/* MAIN */

int			ft_proceed(t_config *config);

/* INIT */

t_config	*ft_init_all(char *argv[]);

/* UTILS */

int			ft_atoi(const char *str);
long long	ft_get_timestamp(void);
void		ft_swap(int	*a, int *b);
void		ft_print_action(t_config *config, int num, char *str);
void		ft_check_end(t_config *config);
void		ft_sleep(long long time);

#endif