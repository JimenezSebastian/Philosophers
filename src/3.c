#include "../include/philo.h"

void	*ft_monitor(void *arg)
{
	t_mem	*mem;
	int		i;
	long	last_meal;
	int 	stop;

	last_meal = 0;
	mem = (t_mem *)arg;
	stop = 1;
	usleep(1000*1000);
	while (stop)
	{
		pthread_mutex_lock(&mem->m_routine_completed);
		if (mem->f_routine_completed == 1)
			stop = 0;
		pthread_mutex_unlock(&mem->m_routine_completed);
		i = 0;
		while (i < mem->n_philo && stop)
		{
			pthread_mutex_lock(&mem->philos[i].m_time_last_meal);
			last_meal = (get_time_ms() - mem->philos[i].time_last_meal);
			pthread_mutex_unlock(&mem->philos[i].m_time_last_meal);
			if (last_meal > mem->time_to_die)
				ft_starv_protocol(mem, i), stop = 0;
			i++;
		}
	}
	return (NULL);
}

void ft_starv_protocol(t_mem *mem, int d)
{	
	int i = 0;

	pthread_mutex_lock(&mem->print_mutex);
	printf("%ld %d Died\n", get_time_ms() - mem->start_time, mem->philos[d].id);
	while (mem->n_philo > i)
	{
		pthread_mutex_lock(&mem->philos[i].m_starvation);
		mem->philos[i].f_starvation = 1;
		pthread_mutex_unlock(&mem->philos[i].m_starvation);
		++i;
	}
	pthread_mutex_unlock(&mem->print_mutex);
}