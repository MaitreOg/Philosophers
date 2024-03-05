/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:31:14 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 17:06:24 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init_philo(t_list *meal)
{
    int i;
    t_philo *philo;

    i = 0;
	philo = malloc(sizeof(t_philo) * meal->n_philo);
    meal->fork = malloc(sizeof (pthread_mutex_t) * meal->n_philo);
    while (i < meal->n_philo)
    {
        philo[i].number = i + 1;
        printf("%d\n", philo[i].number);
        philo[i].last_eat = timecode();
        philo[i].n_eat = 0;
        philo[i].value = *meal;
        pthread_mutex_init(&(meal->fork[i]), NULL);
        pthread_mutex_init(&(philo[i].eaten), NULL);
        pthread_mutex_init(&(philo[i].time_last_eat), NULL);
        if (pthread_create(&(philo[i].id), NULL, &daily, &(philo[i])))
        {
            write(1, "pthread_create failed\n", 22);
            return (0);
        }
        i++;
    }
    return (0);
}