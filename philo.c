/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 19:56:31 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->value->fork[i]));
	printf("philo %d has taken a fork\n", i);
	if (i == 0)
		pthread_mutex_lock(&(philo->value->fork[philo->value->n_philo]));
	else
		pthread_mutex_lock(&(philo->value->fork[i - 1]));
	printf("philo %d has taken a fork\n", i);
	
}

void	eat(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->eaten));
	philo->n_eat += 1;
	printf("philo %d is eaten\n", philo->number);
	pthread_mutex_unlock(&(philo->eaten));
	pthread_mutex_lock(&(philo->time_last_eat));
	philo[i].last_eat = timecode();
	pthread_mutex_unlock(&(philo->time_last_eat));
	pthread_mutex_unlock(&(philo->value->fork[i]));
	if (i == 0)
		pthread_mutex_unlock(&(philo->value->fork[philo->value->n_philo]));
	else
		pthread_mutex_unlock(&(philo->value->fork[i - 1]));
}

void	bed(t_philo	*philo, int i)
{
	printf("philo %d is sleeping\n", i);
	usleep(philo->value->t_sleep);
}

void    *daily(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->number % 2 == 0)
		usleep(15000);
	while (1)
	{
		take_forks(philo, philo->number);
		eat(philo, philo->number);
		bed(philo, philo->number);
		printf("philo %d is thinking\n", philo->number);
		pthread_mutex_lock(&(philo->value->mutex_in_process));
		if (!philo->value->in_process)
		{	
			printf("in procces = 1\n");
			break;
		}
		pthread_mutex_unlock(&(philo->value->mutex_in_process));
		usleep(50);
	}
	//pthread_mutex_unlock(&(philo->value->mutex_in_process));
	return(NULL);
}