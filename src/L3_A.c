/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L3_A.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:38:27 by almejia-          #+#    #+#             */
/*   Updated: 2025/07/04 13:29:09 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->mem->n_philo == 1)
		return (ft_solo_routine(philo));
	ft_barrer_time(philo);
	philo->time_last_meal = get_time_ms();
	while (1)
	{
		ft_safe_print(philo, 4);
		if (ft_verify_starv(philo))
			break ;
		ft_eat(philo);
		if (ft_verify_starv(philo))
			break ;
		ft_sleep(philo);
		if (ft_verify_starv(philo))
			break ;
	}
	ft_set_routine_completed(philo->mem);
	return (NULL);
}

void	*ft_solo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time_last_meal = get_time_ms();
	pthread_mutex_lock(philo->left_fork);
	ft_safe_print(philo, 1);
	usleep(philo->mem->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	ft_lock_forks(philo);
	ft_safe_print(philo, 2);
	pthread_mutex_lock(&philo->m_time_last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->m_time_last_meal);
	usleep(philo->mem->time_to_eat * 1000);
	ft_unlock_forks(philo);
	philo->meals_target--;
}

void	ft_sleep(t_philo *philo)
{
	long	start;
	long	now;

	ft_safe_print(philo, 3);
	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->m_starvation);
		if (philo->f_starvation)
		{
			pthread_mutex_unlock(&philo->m_starvation);
			break ;
		}
		pthread_mutex_unlock(&philo->m_starvation);
		now = get_time_ms();
		if (now - start >= philo->mem->time_to_sleep)
			break ;
		if ((philo->mem->time_to_sleep - (now - start)) < 10)
			usleep(100);
		else
			usleep(500);
	}
}
