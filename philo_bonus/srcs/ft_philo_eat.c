/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:44:23 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/18 23:28:11 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_take_fork(t_config *config, int id)
{
	sem_wait(config->forks);
	ft_print_action(config, id, "has taken a fork");
}

void	ft_throw_fork(t_config *config)
{
	sem_post(config->forks);
}

void	ft_philo_eat(t_config *config, int id)
{
	ft_print_action(config, id, "is eating");
	ft_sleep(config->time_to_eat, config);
}
