/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:08:36 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/19 17:11:02 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_init_philo(t_config *config)
{
	int	index;

	index = config->nb_philo;
	while (--index >= 0)
	{
		config->philo[index].id = index;
		config->philo[index].left_fork_id = index;
		config->philo[index].right_fork_id = (index + 1) % config->nb_philo;
		config->philo[index].last_eat_time = 0;
		config->philo[index].count_eat = 0;
		config->philo[index].config = config;
	}
	return (0);
}

static int	ft_init_mutex(t_config *config)
{
	int	index;

	index = config->nb_philo;
	while (--index >= 0)
	{
		if (pthread_mutex_init(&(config->forks[index]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(config->mutex_writing), NULL))
		return (1);
	if (pthread_mutex_init(&(config->mutex_condition), NULL))
		return (1);
	return (0);
}

t_config	*ft_init_all(char *argv[])
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->nb_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (config->nb_philo >= 200 || config->nb_philo < 1 || \
	config->time_to_die < 1 || config->time_to_eat < 1 || \
	config->time_to_sleep < 1)
		return (NULL);
	if (argv[5])
	{
		config->nb_must_eat = ft_atoi(argv[5]);
		if (config->nb_must_eat < 1)
			return (NULL);
	}
	else
		config->nb_must_eat = -1;
	ft_init_philo(config);
	if (ft_init_mutex(config))
		return (NULL);
	return (config);
}
