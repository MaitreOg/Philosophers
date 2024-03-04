/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/04 19:51:13 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void    take_forks(t_philo *philo, int i)
{
	pthread_mutex_lock(philo[i].l_fork);
	printf("philo %d has taken a fork", i);
	pthread_mutex_lock(philo[i].r_fork);
	printf("philo %d has taken a fork", i);
	
}*/

void	eat(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo[i].eaten));
	philo[i].n_eat += 1;
	pthread_mutex_unlock(&(philo[i].eaten));
	pthread_mutex_lock(&(philo[i].time_last_eat));
	philo[i].last_eat = timecode();
	pthread_mutex_unlock(&(philo[i].time_last_eat));
	//pthread_mutex_lock(philo[i].r_fork);
	//pthread_mutex_lock(philo[i].l_fork);
}

void	bed(t_philo	*philo)
{
	usleep(philo->value.t_sleep);
}

void    *daily(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		usleep(philo->value.t_eat);
	while (1)
	{
		//take_forks(philo, philo->number);
		eat(philo, philo->number);
		bed(philo);
	}
	return(NULL);
}