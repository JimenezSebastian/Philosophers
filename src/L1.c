#include "../include/philo.h"

int ft_L1(t_mem **mem, char **argv)
{
	if (ft_malloc_mem(mem))
		return (1);
	ft_init_mem(*mem);
    if (ft_parse_args(*mem, argv))	
		return (1);
    if (ft_alloc_threads_and_philos(*mem))
		return (1);
	return (0);
}

int 	ft_malloc_mem(t_mem **mem)
{
	*mem = malloc(sizeof(t_mem));
	if (!*mem)
		return (1);
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
