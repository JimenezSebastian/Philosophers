/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:38:02 by almejia-          #+#    #+#             */
/*   Updated: 2025/06/22 14:42:38 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_l1(t_mem **mem, char **argv)
{
	if (ft_malloc_mem(mem))
		return (1);
	if (ft_check_digit_args(argv))
		return (1);
	if (ft_parse_args(*mem, argv))
		return (1);
	if (ft_alloc_threads_and_philos(*mem))
		return (1);
	return (0);
}

int	ft_malloc_mem(t_mem **mem)
{
	*mem = malloc(sizeof(t_mem));
	if (!*mem)
		return (1);
	(*mem)->n_philo = 0;
	(*mem)->time_to_die = 0;
	(*mem)->time_to_eat = 0;
	(*mem)->time_to_sleep = 0;
	(*mem)->must_eat = -1;
	(*mem)->f_routine_completed = 0;
	(*mem)->start_time = 0;
	(*mem)->mutex = NULL;
	(*mem)->threads = NULL;
	(*mem)->philos = NULL;
	return (0);
}

int	ft_check_digit_args(char **argv)
{
	int	a;
	int	b;

	a = 1;
	while (argv[a])
	{
		b = 0;
		while (argv[a][b])
		{
			if (argv[a][b] < '0' || argv[a][b] > '9')
				return (1);
			b++;
		}
		a++;
	}
	return (0);
}

int	ft_parse_args(t_mem *mem, char **argv)
{
	mem->n_philo = ft_atol(argv[1]);
	if (mem->n_philo <= 0 || mem->n_philo > INT_MAX)
		return (1);
	mem->time_to_die = ft_atol(argv[2]);
	if (mem->time_to_die <= 0 || mem->time_to_die > INT_MAX)
		return (1);
	mem->time_to_eat = ft_atol(argv[3]);
	if (mem->time_to_eat <= 0 || mem->time_to_eat > INT_MAX)
		return (1);
	mem->time_to_sleep = ft_atol(argv[4]);
	if (mem->time_to_sleep <= 0 || mem->time_to_sleep > INT_MAX)
		return (1);
	if (argv[5])
	{
		mem->must_eat = ft_atol(argv[5]);
		if (mem->must_eat <= 0 || mem->must_eat > INT_MAX)
			return (1);
	}
	return (0);
}

int	ft_alloc_threads_and_philos(t_mem *mem)
{
	mem->philos = malloc(sizeof(t_philo) * mem->n_philo);
	if (!mem->philos)
		return (1);
	mem->threads = malloc(sizeof(pthread_t) * mem->n_philo);
	if (!mem->threads)
		return (1);
	mem->mutex = malloc(sizeof(pthread_mutex_t) * mem->n_philo);
	if (!mem->mutex)
		return (1);
	return (0);
}
