#include "../include/philo.h"

void	*ft_monitor(void *arg)
{
	t_mem	*mem;
	int		i;
	long	last_meal;

	last_meal = 0;
	mem = (t_mem *)arg;
	while (ft_should_stop(mem) == 0)
	{
		i = 0;
		while (i < mem->n_philo)
		{
			if (ft_is_active(&mem->philos[i]))
			{
				pthread_mutex_lock(&mem->philos[i].m_time_last_meal);
				last_meal = get_time_ms() - mem->philos[i].time_last_meal;
				pthread_mutex_unlock(&mem->philos[i].m_time_last_meal);
				if (last_meal > mem->time_to_die)
					return (ft_starv_protocol(mem, i), NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	ft_is_active(t_philo *philo)
{
	int	active;

	active = 0;
	pthread_mutex_lock(&philo->m_time_last_meal);
	if (philo->time_last_meal > 0)
		active = 1;
	pthread_mutex_unlock(&philo->m_time_last_meal);
	return (active);
}

int	ft_should_stop(t_mem *mem)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&mem->m_routine_completed);
	if (mem->f_routine_completed == 1)
		stop = 1;
	pthread_mutex_unlock(&mem->m_routine_completed);
	return (stop);
}

void	ft_starv_protocol(t_mem *mem, int d)
{
	ft_print_msg(&mem->philos[d], 5);
	
	int	i = 0;
	while (i < mem->n_philo)
	{
		pthread_mutex_lock(&mem->philos[i].m_starvation);
		mem->philos[i].f_starvation = 1;
		pthread_mutex_unlock(&mem->philos[i].m_starvation);
		i++;
	}
}
