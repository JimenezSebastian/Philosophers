#include "../include/philo.h"

int ft_verify(t_philo *philo)
{
	int flag;

	if (philo->meals_eaten == 0)
		return (1);
	flag = 0;
	pthread_mutex_lock(&philo->m_starvation);
	if (philo->f_starvation)
		flag = 1;
	pthread_mutex_unlock(&philo->m_starvation);
	return (flag);
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

void	*ft_solo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->mem->print_mutex);
	printf("%ld %d has taken a fork\n", get_time_ms() - philo->mem->start_time, philo->id);
	pthread_mutex_unlock(&philo->mem->print_mutex);
	usleep(philo->mem->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
