#include "../include/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->mem->must_eat)
		philo->meals_eaten = philo->mem->must_eat;
	if (philo->mem->n_philo == 1)
	{
		ft_solo_routine(philo);
		return (NULL);
	}
	ft_barrer_time(philo);
	philo->time_last_meal = get_time_ms();
	while (1)
	{
		ft_think(philo);
		if (ft_verify_(philo))
			break;
		ft_eat(philo);
		if (ft_verify_(philo))
			break;
		ft_sleep(philo);
		if (ft_verify_(philo))
			break;
	}
	pthread_mutex_lock(&philo->mem->m_routine_completed);
	philo->mem->f_routine_completed = 1;
	pthread_mutex_unlock(&philo->mem->m_routine_completed);
	return (NULL);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_starvation);
	if (!philo->f_starvation)
	{
		pthread_mutex_lock(&philo->mem->print_mutex);
		printf("%ld %d is thinking\n", get_time_ms() - philo->mem->start_time, philo->id);
		pthread_mutex_unlock(&philo->mem->print_mutex);
	}
	pthread_mutex_unlock(&philo->m_starvation);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);

	pthread_mutex_lock(&philo->m_starvation);
	if (!philo->f_starvation)
	{
		pthread_mutex_lock(&philo->mem->print_mutex);
		printf("%ld %d is eating\n", get_time_ms() - philo->mem->start_time, philo->id);
		pthread_mutex_unlock(&philo->mem->print_mutex);
	}
	pthread_mutex_unlock(&philo->m_starvation);

	philo->time_last_meal = get_time_ms();
	philo->meals_eaten--;
	usleep(philo->mem->time_to_eat * 1000);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_starvation);
	if (!philo->f_starvation)
	{
		pthread_mutex_lock(&philo->mem->print_mutex);
		printf("%ld %d is sleeping\n", get_time_ms() - philo->mem->start_time, philo->id);
		pthread_mutex_unlock(&philo->mem->print_mutex);
	}
	pthread_mutex_unlock(&philo->m_starvation);

	usleep(philo->mem->time_to_sleep * 1000);
}

int ft_verify_(t_philo *philo)
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
