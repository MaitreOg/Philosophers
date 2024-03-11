/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:31:14 by smarty            #+#    #+#             */
/*   Updated: 2024/03/11 21:46:13 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_meal(int ac, char **av)
{
	t_list	*meal;
	int		i;

	i = -1;
	meal = malloc(sizeof(t_list));
	meal->n_philo = ft_atoi(av[1]);
	meal->t_die = ft_atoi(av[2]);
	meal->t_eat = ft_atoi(av[3]);
	meal->t_sleep = ft_atoi(av[4]);
	meal->t_day = meal->t_sleep + meal->t_eat;
	meal->stop_meal = 0;
	if (ac == 6)
		meal->target = ft_atoi(av[5]);
	else
		meal->target = -1;
	meal->fork = malloc(sizeof(pthread_mutex_t) * meal->n_philo);
	if (!meal->fork || meal->target == 0)
		return (-1);
	while (++i < meal->n_philo)
		pthread_mutex_init(&(meal->fork[i]), NULL);
	pthread_mutex_init(&(meal->is_alive_mutex), NULL);
	pthread_mutex_init(&(meal->mutex_stop), NULL);
	init_philo(meal);
	return (0);
}

void	init_philo(t_list *meal)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * meal->n_philo);
	meal->is_alive = 1;
	meal->time_lunch = timecode();
	while (++i < meal->n_philo)
	{
		philo[i].number = i + 1;
		philo[i].last_eat = timecode();
		philo[i].n_eat = 0;
		philo[i].value = meal;
		pthread_mutex_init(&(philo[i].eaten), NULL);
		pthread_mutex_init(&(philo[i].time_last_eat), NULL);
		if (pthread_create(&(philo[i].id), NULL, &daily, &(philo[i])))
		{
			write(1, "pthread_create failed\n", 22);
			exit (0);
		}
	}
	alive_and_hungry(philo);
	pthread_mutex_unlock(&(philo->value->mutex_stop));
	end_thread(philo);
	return (free(meal));
}
