/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:38:12 by almejia-          #+#    #+#             */
/*   Updated: 2025/06/22 17:39:45 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_l2(t_mem *mem)
{
	if (ft_init_mutexes(mem))
		return (1);
	ft_init_philos(mem);
	if (ft_create_threads(mem))
		return (1);
	if (ft_create_monitor(mem))
		return (1);
	return (0);
}

int	ft_init_mutexes(t_mem *mem)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&mem->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mem->m_routine_completed, NULL) != 0)
		return (1);
	while (i < mem->n_philo)
	{
		if (pthread_mutex_init(&mem->mutex[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mem->philos[i].m_time_last_meal, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mem->philos[i].m_starvation, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_philos(t_mem *mem)
{
	int	i;

	i = 0;
	while (i < mem->n_philo)
	{
		mem->philos[i].id = i + 1;
		mem->philos[i].time_last_meal = -1;
		mem->philos[i].f_starvation = 0;
		mem->philos[i].left_fork = &mem->mutex[i];
		mem->philos[i].right_fork = &mem->mutex[(i + 1) % mem->n_philo];
		mem->philos[i].mem = mem;
		mem->philos[i].meals_target = -1;
		if (mem->must_eat)
			mem->philos[i].meals_target = mem->must_eat;
		i++;
	}
}

int	ft_create_threads(t_mem *mem)
{
	int	i;

	i = 0;
	mem->start_time = get_time_ms();
	while (i < mem->n_philo)
	{
		if (pthread_create(&mem->threads[i], NULL, &ft_routine,
				&mem->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_create_monitor(t_mem *mem)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &ft_monitor, mem) != 0)
		return (1);
	if (pthread_join(monitor, NULL))
		return (1);
	return (0);
}
