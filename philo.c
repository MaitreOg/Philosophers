/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 17:28:31 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->value.fork[i]));
	printf("philo %d has taken a fork\n", i);
	if (i == 0)
		pthread_mutex_lock(&(philo->value.fork[philo->value.n_philo]));
	else
		pthread_mutex_lock(&(philo->value.fork[i - 1]));
	printf("philo %d has taken a fork\n", i);
	
}

void	eat(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo[i].eaten));
	philo[i].n_eat += 1;
	printf("philo %d is eaten\n", philo->number);
	pthread_mutex_unlock(&(philo[i].eaten));
	pthread_mutex_lock(&(philo[i].time_last_eat));
	philo[i].last_eat = timecode();
	pthread_mutex_unlock(&(philo[i].time_last_eat));
	pthread_mutex_unlock(&(philo->value.fork[i]));
	if (i == 0)
		pthread_mutex_unlock(&(philo->value.fork[philo->value.n_philo]));
	else
		pthread_mutex_unlock(&(philo->value.fork[i - 1]));
}

void	bed(t_philo	*philo, int i)
{
	printf("philo %d is sleeping\n", i);
	usleep(philo->value.t_sleep);
}

void    *daily(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		usleep(1000);
	while (1)
	{
		take_forks(philo, philo->number);
		eat(philo, philo->number);
		bed(philo, philo->number);
		printf("philo %d is thinking\n", philo->number);
	}
	return(NULL);
}