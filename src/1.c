#include "../include/philo.h"

int 	ft_malloc_mem(t_mem **mem)
{
	*mem = malloc(sizeof(t_mem));
	if (!*mem)
		return (1);
	ft_init_mem(*mem);
	return (0);
}

void	ft_init_mem(t_mem *mem)
{
	mem->n_philo = 0;
	mem->time_to_die = 0;
	mem->time_to_eat = 0;
	mem->time_to_sleep = 0;
	mem->must_eat = -1;
	mem->f_routine_completed = 0;
	mem->start_time = 0;
	mem->mutex = NULL;
	mem->threads = NULL;
	mem->philos = NULL;
}

int	ft_parse_args(t_mem *mem, char **argv)
{
	mem->n_philo = ft_atoi(argv[1]);
	mem->time_to_die = ft_atoi(argv[2]);
	mem->time_to_eat = ft_atoi(argv[3]);
	mem->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		mem->must_eat = ft_atoi(argv[5]);
	if (mem->must_eat == 0)
		return (1);
	return (0);
}

int	ft_alloc_threads_and_philos(t_mem *mem)
{
	mem->philos = malloc(sizeof(t_philo) * mem->n_philo);
	if (!mem->philos)
		return (1);
	mem->mutex = malloc(sizeof(pthread_mutex_t) * mem->n_philo);
	if (!mem->mutex)
		return (1);
	mem->threads = malloc(sizeof(pthread_t) * mem->n_philo);
	if (!mem->threads)
		return (1);
	return (0);
}

int	ft_init_mutexes(t_mem *mem)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&mem->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&mem->m_routine_completed, NULL) != 0)
		return (1);
	while (i < mem->n_philo)
	{
		if (pthread_mutex_init(&mem->mutex[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mem->philos[i].m_time_last_meal, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&mem->philos[i].m_starvation, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_philos(t_mem *mem)
{
	int	i;

	i = 0;
	while (i < mem->n_philo)
	{
		mem->philos[i].id = i + 1;
		mem->philos[i].meals_eaten = -1;
		mem->philos[i].time_last_meal = 0;
		mem->philos[i].f_starvation = 0;
		mem->philos[i].left_fork = &mem->mutex[i];
		mem->philos[i].right_fork = &mem->mutex[(i + 1) % mem->n_philo];
		mem->philos[i].mem = mem;
		i++;
	}
}

int	ft_create_threads(t_mem *mem)
{
	int	i;

	i = 0;
	mem->start_time = get_time_ms();
	while (i < mem->n_philo)
	{
		if (pthread_create(&mem->threads[i], NULL, &ft_routine, &mem->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_create_monitor(t_mem *mem)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &ft_monitor, mem) != 0)
		return (1);
	pthread_join(monitor, NULL);
	return (0);
}