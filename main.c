/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:25:24 by smarty            #+#    #+#             */
/*   Updated: 2024/03/19 19:19:01 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_list *meal)
{
	printf("0\t1 has taken a fork\n");
	wait_next(meal->t_die);
	printf("%d\t1 is dead\n", (meal->t_die + 1));
	free(meal);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("pls enter valid arg\n");
		return (-1);
	}
	init_meal(ac, av);
	return (0);
}
