/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:30:11 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/21 04:40:35 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_watchdog(void *void_config)
{
	t_config	*config;

	config = (t_config *)void_config;
	sem_wait(config->sem_die);
	if (config->philo_is_ate)
		return (NULL);
	sem_post(config->sem_die);
	config->philo_is_die = 1;
	ft_sleep(100, config);
	sem_post(config->sem_writing);
	return (NULL);
}

void	ft_cleanup(t_config *config)
{
	sem_close(config->forks);
	sem_close(config->sem_condition);
	sem_close(config->sem_writing);
	sem_close(config->sem_die);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_condition");
	sem_unlink("/philo_die");
	free(config);
}

int	ft_philo_proceed(t_config *config, t_philo *philo)
{
	ft_eat(philo);
	sem_wait(config->sem_condition);
	if (config->philo_is_ate || config->philo_is_die)
	{
		sem_post(config->sem_condition);
		return (1);
	}
	sem_post(config->sem_condition);
	ft_print_action(config, philo->id, "is sleeping");
	ft_sleep(config->time_to_sleep, config);
	ft_print_action(config, philo->id, "is thinking");
	return (0);
}
