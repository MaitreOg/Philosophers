/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:31:14 by smarty            #+#    #+#             */
/*   Updated: 2024/03/19 19:45:26 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_meal2(t_list *meal)
{
	pthread_mutex_init(&(meal->is_alive_mutex), NULL);
	pthread_mutex_init(&(meal->mutex_stop), NULL);
	init_philo(meal);
}

void	init_meal(int ac, char **av)
{
	t_list	*meal;
	int		i;

	i = -1;
	meal = malloc(sizeof(t_list));
	meal->t_die = ft_atoi(av[2]);
	meal->t_eat = ft_atoi(av[3]);
	meal->t_sleep = ft_atoi(av[4]);
	meal->n_philo = ft_atoi(av[1]);
	if (meal->n_philo == 1)
		return (one_philo(meal));
	else if (meal->n_philo == 0)
		return ;
	meal->t_day = meal->t_sleep + meal->t_eat;
	meal->stop_meal = 0;
	if (ac == 6)
		meal->target = ft_atoi(av[5]);
	else
		meal->target = -1;
	meal->fork = malloc(sizeof(pthread_mutex_t) * meal->n_philo);
	if (!meal->fork || meal->target == 0)
		return ;
	while (++i < meal->n_philo)
		pthread_mutex_init(&(meal->fork[i]), NULL);
	init_meal2(meal);
}

void	init_philo(t_list *meal)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * meal->n_philo);
	meal->is_alive = 1;
	meal->is_alive_txt = 1;
	meal->time_lunch = timecode();
	pthread_mutex_init(&(meal->eaten), NULL);
	pthread_mutex_init(&(meal->time_last_eat), NULL);
	while (++i < meal->n_philo)
	{
		philo[i].number = i + 1;
		philo[i].last_eat = timecode();
		philo[i].n_eat = 0;
		philo[i].value = meal;
		if (pthread_create(&(philo[i].id), NULL, &daily, &(philo[i])))
		{
			write(1, "pthread_create failed\n", 22);
			exit (0);
		}
	}
	alive_and_hungry(philo);
	end_thread(philo);
	return (free(meal));
}
