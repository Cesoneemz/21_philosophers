/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:53:55 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/21 03:52:37 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_action(t_config *config, int num, char *str)
{
	sem_wait(config->sem_writing);
	if (!config->philo_is_die)
	{
		printf("%lli ", ft_get_timestamp() - config->timestamp);
		printf("%i ", num + 1);
		printf("%s\n", str);
	}
	sem_post(config->sem_writing);
	return ;
}

void	ft_sleep(long long time, t_config *config)
{
	long long	index;

	(void)config;
	index = ft_get_timestamp();
	usleep(time * 920);
	while (ft_get_timestamp() < index + time)
		usleep(time * 3);
}

static void	ft_exit(t_config *c, t_philo *p)
{
	sem_post(c->sem_condition);
	ft_print_action(c, p->id, "is died");
	sem_wait(c->sem_writing);
	sem_post(c->sem_die);
	c->philo_is_die = 1;
	sem_post(c->forks);
	sem_post(c->forks);
	return ;
}

void	*ft_check_end(void *void_philo)
{
	t_philo		*p;
	t_config	*c;

	p = (t_philo *)void_philo;
	c = p->config;
	while (1)
	{
		sem_wait(c->sem_condition);
		if (ft_get_elapsed_time(p->last_eat_time, ft_get_timestamp()) \
		> c->time_to_die && !c->philo_is_die)
		{
			ft_exit(c, p);
			break ;
		}
		sem_post(c->sem_condition);
		if (c->philo_is_die)
			break ;
		if (p->count_eat >= c->nb_must_eat && c->nb_must_eat != -1)
		{
			c->philo_is_ate = 1;
			break ;
		}
	}	
	return (NULL);
}
