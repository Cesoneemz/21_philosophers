/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:44:23 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/21 02:23:05 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_fork(t_config *config, int id)
{
	sem_wait(config->sem_condition);
	if (config->philo_is_die)
	{
		sem_post(config->sem_condition);
		return ;
	}
	sem_post(config->sem_condition);
	sem_wait(config->forks);
	ft_print_action(config, id, "has taken a fork");
}

void	ft_throw_fork(t_config *config)
{
	sem_post(config->forks);
}

void	ft_philo_eat(t_config *config, int id)
{
	sem_wait(config->sem_condition);
	if (config->philo_is_die)
	{
		sem_post(config->sem_condition);
		return ;
	}
	sem_post(config->sem_condition);
	ft_print_action(config, id, "is eating");
	ft_sleep(config->time_to_eat, config);
}
