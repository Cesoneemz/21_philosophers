/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:28:38 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/19 00:11:24 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_eat(t_philo *philo)
{
	t_config	*config;

	config = philo->config;
	ft_take_fork(config, philo->id);
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
	if (philo->id % 2)
		usleep(5000);
	while (!config->philo_is_die)
	{
		ft_eat(philo);
		if (config->philo_is_ate || config->philo_is_die)
			break ;
		ft_print_action(config, philo->id, "is sleeping");
		ft_sleep(config->time_to_sleep, config);
		ft_print_action(config, philo->id, "is thinking");
	}
	return ;
}

static void	ft_exit_proceed(t_config *config)
{
	int	index;
	int	result;

	index = 0;
	while (index < config->nb_philo)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
		{
			index = -1;
			while (++index < config->nb_philo)
				kill(config->philo[index].process_id, 15);
			break ;
		}
		index++;
	}
	sem_close(config->forks);
	sem_close(config->sem_eating);
	sem_close(config->sem_condition);
	sem_close(config->sem_writing);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_condition");
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
