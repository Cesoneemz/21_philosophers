/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:28:38 by wlanette          #+#    #+#             */
/*   Updated: 2022/04/28 21:18:56 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_eat(t_philo *philo)
{
	t_config	*config;
	int			max_fork_id;
	int			min_fork_id;

	config = philo->config;
	max_fork_id = philo->right_fork_id;
	min_fork_id = philo->left_fork_id;
	if (min_fork_id > max_fork_id)
		ft_swap(&min_fork_id, &max_fork_id);
	pthread_mutex_lock(&config->forks[min_fork_id]);
	ft_print_action(config, philo->id, "has taken a fork");
	pthread_mutex_lock(&config->forks[max_fork_id]);
	ft_print_action(config, philo->id, "has taken a fork");
	ft_print_action(config, philo->id, "is eating");
	ft_sleep(config->time_to_eat);
	pthread_mutex_lock(&config->mutex_condition);
	(philo->count_eat)++;
	philo->last_eat_time = ft_get_timestamp();
	pthread_mutex_unlock(&config->mutex_condition);
	pthread_mutex_unlock(&config->forks[max_fork_id]);
	pthread_mutex_unlock(&config->forks[min_fork_id]);
}

void	*ft_philo(void *void_philo)
{
	t_philo		*philo;
	t_config	*config;

	philo = (t_philo *)void_philo;
	config = philo->config;
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&(config->mutex_condition));
		if (config->philo_is_die || config->philo_is_ate)
		{
			pthread_mutex_unlock(&(config->mutex_condition));
			break ;
		}
		pthread_mutex_unlock(&(config->mutex_condition));
		ft_print_action(config, philo->id, "is sleeping");
		ft_sleep(config->time_to_sleep);
		ft_print_action(config, philo->id, "is thinking");
	}
	return (NULL);
}

static void	ft_exit_proceed(t_config *config)
{
	int	index;

	index = -1;
	while (++index < config->nb_philo)
		pthread_join(config->philo[index].thread_id, NULL);
	index = -1;
	while (++index < config->nb_philo)
		pthread_mutex_destroy(&config->forks[index]);
	pthread_mutex_destroy(&config->mutex_writing);
	pthread_mutex_destroy(&config->mutex_eating);
	pthread_mutex_destroy(&config->mutex_condition);
}

int	ft_proceed(t_config *config)
{
	int		index;
	t_philo	*philo;

	index = 0;
	config->timestamp = ft_get_timestamp();
	config->philo_is_die = 0;
	config->philo_is_ate = 0;
	philo = config->philo;
	while (index < config->nb_philo)
	{
		philo[index].last_eat_time = ft_get_timestamp();
		if (pthread_create(&(philo[index].thread_id), NULL, ft_philo, \
		&(philo[index])))
			return (1);
		index++;
	}
	ft_check_end(config);
	ft_exit_proceed(config);
	return (0);
}