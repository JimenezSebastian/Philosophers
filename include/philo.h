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
	// Args entrada
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	// var protegida : 
	int				f_routine_completed;
	pthread_mutex_t m_routine_completed;

	// Propiedades Nodos Philo 
	struct s_philo	*philos;
	pthread_mutex_t	*mutex;
	pthread_t		*threads;

	// Mutex print
	pthread_mutex_t	print_mutex;
	
	// Tiempo Inicio
	long			start_time;
	
}	t_mem;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				meals_eaten;
	
	// Var protegida Revision tiempos
	long			time_last_meal;
	pthread_mutex_t m_time_last_meal;

	// Flag monitor - hilo inanicion
	int				f_starvation;
	pthread_mutex_t m_starvation;

	t_mem			*mem;

}	t_philo;

//L1 -  Malloc Mem 
int 	ft_L1(t_mem **mem, char **argv);
int		ft_malloc_mem(t_mem **mem);
void	ft_init_mem(t_mem *mem);
int		ft_parse_args(t_mem *mem, char **argv);
int		ft_alloc_threads_and_philos(t_mem *mem);

//L2 -  Mutex & Threads
int 	ft_L2(t_mem *mem);
int		ft_init_mutexes(t_mem *mem);
void	ft_init_philos(t_mem *mem);
int		ft_create_threads(t_mem *mem);
int		ft_create_monitor(t_mem *mem);

//L3 -  Routine Principal Thread
void	*ft_routine(void *arg);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

//L3 -  Routine Principal Thread - B 
int		ft_verify(t_philo *philo);
void	ft_barrer_time(t_philo *philo);
void	*ft_solo_routine(void *arg);

//L4 -  Monitor Thread 
void	*ft_monitor(void *arg);
void	ft_starv_protocol(t_mem *mem, int d);

//LCE  -  Clean Exit
void ft_LCE(t_mem *mem);
void	ft_graceful_shutedown(t_mem *mem);

//LG -  General Utils
long	get_time_ms(void);

#endif

// Doc Arquitectura Programa 

// L (layer) [capa] Etiqupe				eta Descriptora
 // - Se agrega despues 
// Ext : Responsabilidad -> Evol :  Mayor A _ B _ C
 
// L Clean_Exit.c * Ultima capa del hilo cronologico de eventos.
// L General_Utils.c * Caja de herramientas * hojas 