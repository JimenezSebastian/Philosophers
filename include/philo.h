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

	// var protegida : aviso
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

	int				meals_target;
	
	// Var protegida Revision tiempos
	long			time_last_meal;
	pthread_mutex_t m_time_last_meal;

	// Flag monitor - hilo inanicion
	int				f_starvation;
	pthread_mutex_t m_starvation;

	t_mem			*mem;
}	t_philo;

//L1 -  Reserva Base de Memoria 
int 	ft_L1(t_mem **mem, char **argv);
int		ft_malloc_mem(t_mem **mem);
int		ft_parse_args(t_mem *mem, char **argv);
int		ft_alloc_threads_and_philos(t_mem *mem);
int		ft_check_digit_args(char **argv);

//L2 -  pthread : Mutex & Threads
int 	ft_L2(t_mem *mem);
int		ft_init_mutexes(t_mem *mem);
void	ft_init_philos(t_mem *mem);
int		ft_create_threads(t_mem *mem);
int		ft_create_monitor(t_mem *mem);

//L3 -  Routine Principal Thread
void	*ft_routine(void *arg);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);


//L3 -  Routine Principal Thread - B 
void	*ft_solo_routine(void *arg);
void	ft_barrer_time(t_philo *philo);
int		ft_verify_starv(t_philo *philo);
void	ft_set_routine_completed(t_mem *mem);

//L4 -  Monitor Thread 
void	*ft_monitor(void *arg);
int		ft_is_active(t_philo *philo);
void	ft_starv_protocol(t_mem *mem, int d);
int		ft_should_stop(t_mem *mem);
void	ft_lock_forks(t_philo *philo);

//LCE  -  Clean Exit
void 	ft_LCE(t_mem *mem);
void	ft_graceful_shutedown(t_mem *mem);

//LG -  General Utils
long	get_time_ms(void);
long	ft_atol(const char *str);
void	ft_print_msg(t_philo *philo, int flag);
void	ft_safe_print(t_philo *philo, int flag);

#endif

// Doc Arquitectura Programa 

// L (layer) [capa] Etiqupe				eta Descriptora
 // - Se agrega despues 
// Ext : Responsabilidad -> Evol :  Mayor A _ B _ C
 
// L Clean_Exit.c * Ultima capa del hilo cronologico de eventos.
// L General_Utils.c * Caja de herramientas * hojas 