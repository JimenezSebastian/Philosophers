/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LGU.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:39:28 by almejia-          #+#    #+#             */
/*   Updated: 2025/06/22 14:39:29 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	ft_safe_print(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->m_starvation);
	if (philo->f_starvation == 0 && flag != 5)
		ft_print_msg(philo, flag);
	else if (flag == 5)
		ft_print_msg(philo, flag);
	pthread_mutex_unlock(&philo->m_starvation);
}

void	ft_print_msg(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->mem->print_mutex);
	if (flag == 1)
		printf("%ld %d has taken a fork\n", get_time_ms()
			- philo->mem->start_time, philo->id);
	else if (flag == 2)
		printf("%ld %d is eating\n", get_time_ms() - philo->mem->start_time,
			philo->id);
	else if (flag == 3)
		printf("%ld %d is sleeping\n", get_time_ms() - philo->mem->start_time,
			philo->id);
	else if (flag == 4)
		printf("%ld %d is thinking\n", get_time_ms() - philo->mem->start_time,
			philo->id);
	else if (flag == 5)
		printf("%ld %d died\n", get_time_ms() - philo->mem->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->mem->print_mutex);
}
