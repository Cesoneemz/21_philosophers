/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:53:55 by wlanette          #+#    #+#             */
/*   Updated: 2022/04/28 21:13:01 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_action(t_config *config, int num, char *str)
{
	pthread_mutex_lock(&(config->mutex_writing));
	if (!(config->philo_is_die))
	{
		printf("%lli ", ft_get_timestamp() - config->timestamp);
		printf("%i ", num + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(config->mutex_writing));
	return ;
}

static int	ft_check_death(t_philo *philo, int time_to_die)
{
	if ((ft_get_timestamp() - philo->last_eat_time) > time_to_die)
		return (1);
	return (0);
}

static int	ft_check_ate(t_philo *philo, int nb_must_eat)
{
	if (philo->count_eat >= nb_must_eat)
		return (1);
	return (0);
}

void	ft_sleep(long long time)
{
	long long	index;

	index = ft_get_timestamp();
	while ((ft_get_timestamp() - index) >= time)
		usleep(10);
}

void	ft_check_end(t_config *config)
{
	int	index;

	while (1)
	{
		index = 0;
		pthread_mutex_lock(&(config->mutex_condition));
		while (index < config->nb_philo)
		{
			if (ft_check_death(&config->philo[index], config->time_to_die))
			{
				ft_print_action(config, config->philo[index].id, "is died");
				config->philo_is_die = 1;
				break ;
			}
			if (ft_check_ate(&config->philo[index], config->nb_must_eat) \
			&& config->nb_must_eat != -1)
			{
				config->philo_is_ate = 1;
				break ;
			}
			index++;
		}
		pthread_mutex_unlock(&(config->mutex_condition));
		usleep(100);
		if (config->philo_is_die || config->philo_is_ate)
			break ;
	}
}
