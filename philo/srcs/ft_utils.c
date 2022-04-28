/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:09:23 by wlanette          #+#    #+#             */
/*   Updated: 2022/04/28 19:51:07 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' \
			|| c == '\v');
}

static int	ft_get_result_if_overflow(int minus)
{
	if (minus > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					minus;
	size_t				counter;

	result = 0;
	minus = 1;
	counter = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		minus *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		if (result >= 9223372036854775808ULL || counter >= 25)
			return (ft_get_result_if_overflow(minus));
		counter++;
		str++;
	}
	return ((int)result * minus);
}

long long	ft_get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_swap(int	*a, int *b)
{
	int	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}
