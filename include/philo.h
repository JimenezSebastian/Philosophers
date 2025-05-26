# ifndef PHILO_H
#define PHILO_H

#include "../libft/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_mem
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	int				f_routine_completed;
	pthread_mutex_t m_routine_completed;

	struct s_philo	*philos;
	pthread_mutex_t	*mutex;
	pthread_t		*threads;

	pthread_mutex_t	print_mutex;
	
	long			start_time;
	
}	t_mem;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				meals_eaten;
	
	// Revision tiempos
	long			time_last_meal;
	pthread_mutex_t m_time_last_meal;

	// Flag monitor - hilo inanicion
	int				f_starvation;
	pthread_mutex_t m_starvation;

	t_mem			*mem;

}	t_philo;

// 1
int		ft_malloc_mem(t_mem **mem);
void	ft_init_mem(t_mem *mem);
int		ft_parse_args(t_mem *mem, char **argv);
int		ft_alloc_threads_and_philos(t_mem *mem);
int		ft_init_mutexes(t_mem *mem);
void	ft_init_philos(t_mem *mem);
int		ft_create_threads(t_mem *mem);
int		ft_create_monitor(t_mem *mem);


// 2 
void	*ft_routine(void *arg);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_verify_(t_philo *philo);
void	ft_barrer_time(t_philo *philo);
void	*ft_solo_routine(void *arg);

// 3 
void	*ft_monitor(void *arg);
void	ft_starv_protocol(t_mem *mem, int d);

// exit clean
void	ft_cleanup(t_mem *mem);
// utils.c
long	get_time_ms(void);
#endif
