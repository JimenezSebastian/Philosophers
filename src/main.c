/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almejia- < almejia-@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:40:40 by almejia-          #+#    #+#             */
/*   Updated: 2025/06/22 14:42:51 by almejia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_controller(char **argv)
{
	t_mem	*mem;

	if (ft_l1(&mem, argv))
		return (1);
	if (ft_l2(mem))
		return (1);
	ft_lce(mem);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(1, "Error : Args", 12), 1);
	if (ft_controller(argv))
		return (write(1, "Error : 404", 11), 1);
	return (0);
}
