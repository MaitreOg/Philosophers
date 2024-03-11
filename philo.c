/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/11 18:33:31 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead(t_philo *philo)
{
	print_status(philo, "is dead");
	pthread_mutex_lock(&philo->value->is_alive_mutex);
	philo->value->is_alive = 0;
	pthread_mutex_unlock(&philo->value->is_alive_mutex);
}
void	alive_and_hungry(t_philo  *philo)
{
	int	i;
	int	bool;

	while(1)
	{
		i = -1;
		bool = 1;
		while(++i < philo->value->n_philo)
		{
			pthread_mutex_lock(&(philo->time_last_eat));
			if (timecode() - philo[i].last_eat > philo->value->t_die)
			{
				dead(&philo[i]);
				exit(0);
			}
			pthread_mutex_unlock(&(philo->time_last_eat));
			pthread_mutex_lock(&(philo->eaten));
			if (philo->value->target > philo[i].n_eat && philo->value->target != -1)
				bool = 0;
			if (philo->value->target == -1)
				bool = 0;
			pthread_mutex_unlock(&(philo->eaten));
		}
		pthread_mutex_lock(&(philo->value->mutex_stop));
		if (bool == 1)
		{
			philo->value->stop_meal = 1;
			usleep((philo->value->t_day + 10) * 1000);
			exit(0);
		}
		pthread_mutex_unlock(&(philo->value->mutex_stop));
	}

	
}

void	end_thread(t_philo *philo, int i)
{
	while (--i > 0)
		pthread_join(philo[i].id, NULL);
	i = -1;
	pthread_mutex_destroy(&(philo->value->routine));
	pthread_mutex_destroy(&(philo->value->is_alive_mutex));
	pthread_mutex_destroy(&(philo->value->mutex_stop));
	pthread_mutex_destroy(&(philo->eaten));
	pthread_mutex_destroy(&(philo->time_last_eat));
	while (++i < philo->value->n_philo)
	{
		pthread_mutex_destroy(&(philo->value->fork[i]));
		free(&philo->value->fork[i]);
		free(&philo[i]);
	}
	free(philo->value);
	
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
		usleep(philo->value->t_eat * 1000);
	while (philo->value->stop_meal == 0)
	{
		pthread_mutex_lock(&(philo->value->routine));
		take_forks(philo, l_fork, r_fork);
		eat(philo, l_fork, r_fork);
		bed(philo);
		pthread_mutex_lock(&(philo->value->is_alive_mutex));
		if (philo->value->is_alive == 0)
			break;
		pthread_mutex_unlock(&(philo->value->is_alive_mutex));
	}
	pthread_mutex_unlock(&(philo->value->routine));
	pthread_mutex_unlock(&(philo->value->is_alive_mutex));
	return(NULL);
}