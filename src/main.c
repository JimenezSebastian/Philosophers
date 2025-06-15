#include "../include/philo.h"

int ft_controller(char **argv)
{
    t_mem *mem;
    
    if (ft_L1(&mem, argv))
        return (1);
    if (ft_L2(mem))
        return (1);
    ft_LCE(mem);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (write(1, "Error : Args", 12), 1);
    if (ft_controller(argv))
        return (write(1, "Error : 404", 11), 1);
    return (0);
}