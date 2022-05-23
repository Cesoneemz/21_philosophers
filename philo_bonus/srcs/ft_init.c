/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:08:36 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/23 21:16:46 by wlanette         ###   ########.fr       */
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
		config->philo[index].last_eat_time = 0;
		config->philo[index].count_eat = 0;
		config->philo[index].config = config;
	}
	return (0);
}

static int	ft_init_sem(t_config *config)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_condition");
	sem_unlink("/philo_die");
	config->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, \
	config->nb_philo);
	config->sem_writing = sem_open("/philo_writing", O_CREAT, S_IRWXU, 1);
	config->sem_condition = sem_open("/philo_condition", O_CREAT, S_IRWXU, 1);
	config->sem_die = sem_open("/philo_die", O_CREAT, S_IRWXU, 1);
	if (config->forks == SEM_FAILED || config->sem_writing == SEM_FAILED || \
	config->sem_condition == SEM_FAILED || config->sem_die == SEM_FAILED)
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
	if (ft_init_sem(config))
		return (NULL);
	return (config);
}
