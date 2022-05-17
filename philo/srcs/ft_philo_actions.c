/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:53:55 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/17 20:13:27 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_action(t_config *config, int num, char *str)
{
	pthread_mutex_lock(&(config->mutex_writing));
	if (!config->philo_is_die)
	{
		printf("%lli ", ft_get_timestamp() - config->timestamp);
		printf("%i ", num + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(config->mutex_writing));
	return ;
}

static int	ft_check_death(t_philo *philo, t_config *config)
{
	pthread_mutex_lock(&config->mutex_condition);
	if (ft_get_elapsed_time(philo->last_eat_time, ft_get_timestamp()) > config->time_to_die)
	{
		pthread_mutex_lock(&(config->mutex_writing));
		printf("%lli %i %s\n", ft_get_timestamp() - config->timestamp, philo->id + 1, "is died");
		config->philo_is_die = 1;
		return (1);
	}
	pthread_mutex_unlock(&config->mutex_condition);
	return (0);
}

static int	ft_check_ate(t_config *config)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (index < config->nb_philo)
	{
		pthread_mutex_lock(&config->mutex_condition);
		if (config->philo[index].count_eat >= config->nb_must_eat)
			counter++;
		pthread_mutex_unlock(&config->mutex_condition);
		index++;
	}
	if (counter == config->nb_philo)
	{
		pthread_mutex_lock(&config->mutex_condition);
		return (1);
	}
	return (0);
}

void	ft_sleep(long long time, t_config *config)
{
	long long	index;

	index = ft_get_timestamp();
	while (!config->philo_is_die && ft_get_timestamp() < index + time)
		usleep(10);
}

void	ft_check_end(t_config *config)
{
	int	index;

	while (1)
	{
		index = -1;
		while (++index < config->nb_philo)
		{
			if (ft_check_death(&config->philo[index], config))
				return ;
			ft_sleep(100, config);
		}
		if (config->nb_must_eat != -1)
		{
			if (ft_check_ate(config))
				return ;
		}
	}	
}
