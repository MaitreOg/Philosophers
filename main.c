/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:25:24 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 17:22:33 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main (int ac, char **av)
{
	t_list	*meal;
		
	if (ac != 5 && ac != 6)
		return (-1);

	meal = malloc(sizeof(t_list));
	meal->n_philo = ft_atoi(av[1]);
	meal->t_die = ft_atoi(av[2]);
	meal->t_eat = ft_atoi(av[3]);
	meal->t_sleep = ft_atoi(av[4]);
	meal->t_day = meal->t_sleep + meal->t_eat;
	if (ac == 6)
		meal->target = ft_atoi(av[5]);
	init_philo(meal);
	
}