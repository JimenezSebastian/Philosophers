/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LCE.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:39:16 by almejia-          #+#    #+#             */
/*   Updated: 2025/06/22 14:41:56 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_lce(t_mem *mem)
{
	ft_graceful_shutedown(mem);
}

void	ft_graceful_shutedown(t_mem *mem)
{
	int	i;

	i = 0;
	while (i < mem->n_philo)
	{
		pthread_join(mem->threads[i], NULL);
		i++;
	}
	ft_destroy_mutexes(mem);
	free(mem->threads);
	free(mem->mutex);
	free(mem->philos);
	free(mem);
}

void	ft_destroy_mutexes(t_mem *mem)
{
	int	i;

	i = 0;
	while (i < mem->n_philo)
	{
		pthread_mutex_destroy(&mem->mutex[i]);
		i++;
	}
	i = 0;
	while (i < mem->n_philo)
	{
		pthread_mutex_destroy(&mem->philos[i].m_time_last_meal);
		pthread_mutex_destroy(&mem->philos[i].m_starvation);
		i++;
	}
	pthread_mutex_destroy(&mem->print_mutex);
	pthread_mutex_destroy(&mem->m_routine_completed);
}
