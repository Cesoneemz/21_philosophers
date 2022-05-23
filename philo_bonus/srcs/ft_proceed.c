/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:28:38 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/23 20:45:39 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_philo *philo)
{
	t_config	*config;

	config = philo->config;
	ft_take_fork(config, philo->id);
	if (config->nb_philo == 1)
	{
		while (!config->philo_is_die)
			ft_sleep(10, config);
		return ;
	}
	ft_take_fork(config, philo->id);
	ft_philo_eat(config, philo->id);
	sem_wait(config->sem_condition);
	(philo->count_eat)++;
	philo->last_eat_time = ft_get_timestamp();
	sem_post(config->sem_condition);
	ft_throw_fork(config);
	ft_throw_fork(config);
}

void	ft_philo(void *void_philo)
{
	t_config	*config;
	t_philo		*philo;

	philo = (t_philo *)void_philo;
	config = philo->config;
	philo->last_eat_time = ft_get_timestamp();
	pthread_create(&(philo->check_death), NULL, ft_check_end, void_philo);
	pthread_create(&(philo->watchdog), NULL, ft_watchdog, (void *)config);
	while (!config->philo_is_die && !config->philo_is_ate)
	{
		if (ft_philo_proceed(config, philo))
			break ;
	}
	sem_post(config->sem_die);
	pthread_join(philo->check_death, NULL);
	pthread_join(philo->watchdog, NULL);
	sem_post(config->sem_writing);
	ft_cleanup(config);
	exit(0);
}

static void	ft_exit_proceed(t_config *config)
{
	int	index;
	int	result;
	int	status;

	index = 0;
	result = 0;
	while (index < config->nb_philo)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
		{
			index = -1;
			while (++index < config->nb_philo)
				waitpid(-1, &status, 0);
			break ;
		}
		index++;
	}
	ft_cleanup(config);
}

int	ft_proceed(t_config *config)
{
	int		index;
	t_philo	*philo;

	index = -1;
	config->timestamp = ft_get_timestamp();
	config->philo_is_die = 0;
	config->philo_is_ate = 0;
	philo = config->philo;
	sem_wait(config->sem_die);
	while (++index < config->nb_philo)
	{
		philo[index].process_id = fork();
		if (philo[index].process_id < 0)
			return (1);
		if (philo[index].process_id == 0)
			ft_philo(&philo[index]);
		usleep(100);
	}
	ft_exit_proceed(config);
	return (0);
}
