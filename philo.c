/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 20:33:34 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(philo->value->fork[r_fork]));
	printf("philo %d has taken a fork\n", philo->number);
	pthread_mutex_lock(&(philo->value->fork[l_fork]));
	printf("philo %d has taken a fork\n", philo->number);
	
}

void	eat(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(philo->eaten));
	philo->n_eat += 1;
	printf("philo %d is eaten\n", philo->number);
	pthread_mutex_unlock(&(philo->eaten));
	pthread_mutex_lock(&(philo->time_last_eat));
	philo->last_eat = timecode();
	pthread_mutex_unlock(&(philo->time_last_eat));
	pthread_mutex_unlock(&(philo->value->fork[r_fork]));
	pthread_mutex_unlock(&(philo->value->fork[l_fork]));
}

void	bed(t_philo	*philo, int i)
{
	printf("philo %d is sleeping\n", i);
	usleep(philo->value->t_sleep);
}

void	end_thread(t_philo *philo, int i)
{
	while (--i > 0)
	{
		pthread_join(philo[i].id, NULL);
	}
}

void    *daily(void *arg)
{
	t_philo	*philo;
	int l_fork;
	int r_fork;

	philo = (t_philo *)arg;
	r_fork = philo->number - 1;
	l_fork = philo->number - 1 - 1;
	if (l_fork < 0)
		l_fork = philo->value->n_philo - 1;
	if (philo->number % 2 == 0)
		usleep(philo->value->t_day + 100);
	while (1)
	{
		take_forks(philo, l_fork, r_fork);
		eat(philo, l_fork, r_fork);
		bed(philo, philo->number);
		printf("philo %d is thinking\n", philo->number);
		pthread_mutex_lock(&(philo->value->mutex_in_process));
		if (!philo->value->in_process)
			break;
		pthread_mutex_unlock(&(philo->value->mutex_in_process));
		usleep(50);
	}
	pthread_mutex_unlock(&(philo->value->mutex_in_process));
	return(NULL);
}