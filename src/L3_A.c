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
			break;
		ft_eat(philo);
		if (ft_verify_starv(philo))
			break;
		ft_sleep(philo);
		if (ft_verify_starv(philo))
			break;
	}
	ft_set_routine_completed(philo->mem); // desactiva el monitor por cumplimiento de tareas.
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

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	philo->meals_target--;
}

void	ft_sleep(t_philo *philo)
{
	long	start;
	long	now;

	start = get_time_ms();
	ft_safe_print(philo, 3);
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
		usleep(500);
	}
}