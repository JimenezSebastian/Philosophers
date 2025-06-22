#include "../include/philo.h"

void	*ft_solo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	ft_safe_print(philo, 1);
	usleep(philo->mem->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	ft_barrer_time(t_philo *philo)
{
	int		group;
	long	delay;
	long	now;
	long	target_time;

	group = philo->id % 3;
	delay = group * (philo->mem->time_to_eat);
	target_time = philo->mem->start_time + delay;
	
	now = get_time_ms();
	while (now < target_time)
	{
		usleep(100);
		now = get_time_ms();
	}
}

int ft_verify_starv(t_philo *philo)
{
	int flag;

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
	if (philo->id % 2 == 0)
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