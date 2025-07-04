/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L3_B.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:38:40 by almejia-          #+#    #+#             */
/*   Updated: 2025/07/04 13:29:35 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_barrer_time(t_philo *philo)
{
	int		group;
	long	start_delay;

	group = philo->id % 3;
	start_delay = group * (philo->mem->time_to_eat / 2);
	while (get_time_ms() - philo->mem->start_time < start_delay)
		usleep(50);
}

int	ft_verify_starv(t_philo *philo)
{
	int	flag;

	if (philo->meals_target == 0)
		return (1);
	flag = 0;
	pthread_mutex_lock(&philo->m_starvation);
	if (philo->f_starvation)
		flag = 1;
	pthread_mutex_unlock(&philo->m_starvation);
	return (flag);
}

void	ft_set_routine_completed(t_mem *mem)
{
	pthread_mutex_lock(&mem->m_routine_completed);
	mem->f_routine_completed = 1;
	pthread_mutex_unlock(&mem->m_routine_completed);
}

void	ft_lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->mem->n_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		ft_safe_print(philo, 1);
		ft_safe_print(philo, 1);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		ft_safe_print(philo, 1);
		ft_safe_print(philo, 1);
	}
}

void	ft_unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->mem->n_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
