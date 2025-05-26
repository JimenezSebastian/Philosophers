#include "../include/philo.h"

void ft_controller(char **argv)
{
    t_mem *mem;
    
    // Layer 1  
    ft_malloc_mem(&mem);
    if (ft_parse_args(mem, argv))
        exit(1);
    ft_alloc_threads_and_philos(mem);
    ft_init_mutexes(mem);
    ft_init_philos(mem);

    // Create threads 
    ft_create_threads(mem);
    ft_create_monitor(mem);
    
    // Exit clean 
    ft_cleanup(mem);
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        printf("Perror");    
    ft_controller(argv);
    return (0);
}