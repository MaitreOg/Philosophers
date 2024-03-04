/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:31:14 by smarty            #+#    #+#             */
/*   Updated: 2024/03/04 19:10:45 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init_philo(t_list *meal)
{
    int i;
    t_philo *philo;

    i = 0;
	philo = malloc(sizeof(t_philo) * meal->n_philo);
    while (i < meal->n_philo)
    {
        philo[i].number = i + 1;
        philo[i].last_eat = timecode();
        philo[i].n_eat = 0;
        philo[i].value = meal;
        pthread_mutex_init(philo[i].l_fork, NULL);
        pthread_mutex_init(philo[i].r_fork, NULL);
        pthread_mutex_init(philo[i].eaten, NULL);
        pthread_mutex_init(philo[i].time_last_eat, NULL);
        if (pthread_create(&(philo[i].id), NULL, &daily, &(philo[i])))
        {
            write(1, "pthread_create failed\n", 22);
            return (0);
        }
        i++;
    }
    return (0);
}