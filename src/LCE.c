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
	i = 0;
	while (i < mem->n_philo)
	{
		pthread_mutex_destroy(&mem->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&mem->print_mutex);
	free(mem->threads);
	free(mem->mutex);
	free(mem->philos);
	free(mem);
}
