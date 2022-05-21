/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:06:30 by wlanette          #+#    #+#             */
/*   Updated: 2022/05/21 03:19:49 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_write_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

static int	ft_check_args(char *argv[])
{
	int	index;
	int	jndex;

	index = 1;
	while (argv[index])
	{
		jndex = 0;
		while (argv[index][jndex])
		{
			if (!(argv[index][jndex] >= '0') || !(argv[index][jndex] <= '9'))
				return (1);
			jndex++;
		}
		index++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_config	*config;

	if (argc != 5 && argc != 6)
		return (ft_write_error("Wrong amount of arguments"));
	if (ft_check_args(argv))
		return (ft_write_error("Wrong arguments"));
	config = ft_init_all(argv);
	if (!config)
		return (ft_write_error("Error while initialization"));
	if (ft_proceed(config))
		return (ft_write_error("Error while working"));
	return (0);
}
