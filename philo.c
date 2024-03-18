/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:19:15 by smarty            #+#    #+#             */
/*   Updated: 2024/03/18 21:53:21 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive(t_philo *philo, int i)
{
	pthread_mutex_lock(&(philo->value->time_last_eat));
	if (timecode() - philo[i].last_eat > philo->value->t_die)
	{
		dead(&philo[i]);
		pthread_mutex_unlock(&(philo->value->time_last_eat));
		return (0);
	}
	pthread_mutex_unlock(&(philo->value->time_last_eat));
	return (1);
}

int	hungry(t_philo *philo, int bool)
{
	pthread_mutex_lock(&(philo->value->mutex_stop));
	if (bool == 1)
	{
		philo->value->stop_meal = 1;
		usleep((philo->value->t_day + 10) * 1000);
		pthread_mutex_unlock(&(philo->value->mutex_stop));
		return (0);
	}
	pthread_mutex_unlock(&(philo->value->mutex_stop));
	return (1);
}

void	alive_and_hungry(t_philo *philo)
{
	int	i;
	int	bool;

	while (1)
	{
		i = -1;
		bool = 1;
		while (++i < philo->value->n_philo)
		{
			if (alive(philo, i) == 0)
				return ;
			pthread_mutex_lock(&(philo->value->eaten));
			if (philo->value->target > philo[i].n_eat && \
						philo->value->target != -1)
				bool = 0;
			if (philo->value->target == -1)
				bool = 0;
			pthread_mutex_unlock(&(philo->value->eaten));
		}
		if (hungry(philo, bool) == 0)
		{
			pthread_mutex_lock(&philo->value->is_alive_mutex);
			philo->value->is_alive = 0;
			pthread_mutex_unlock(&philo->value->is_alive_mutex);
			return ;
		}
	}
}

void	end_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->value->n_philo)
		pthread_join(philo[i].id, NULL);
	i = -1;
	pthread_mutex_destroy(&(philo->value->is_alive_mutex));
	pthread_mutex_destroy(&(philo->value->mutex_stop));
	pthread_mutex_destroy(&(philo->value->eaten));
	pthread_mutex_destroy(&(philo->value->time_last_eat));
	while (++i < philo->value->n_philo)
		pthread_mutex_destroy(&(philo->value->fork[i]));
	free(philo->value->fork);
	free(philo);
}

void	*daily(void *arg)
{
	t_philo	*philo;
	int		l_fork;
	int		r_fork;

	philo = (t_philo *)arg;
	r_fork = philo->number - 1;
	l_fork = philo->number - 1 - 1;
	if (l_fork < 0)
		l_fork = philo->value->n_philo - 1;
	if (philo->number % 2)
		usleep(philo->value->t_eat * 1000);
	while (1)
	{
		take_forks(philo, l_fork, r_fork);
		eat(philo, l_fork, r_fork);
		bed(philo);
		pthread_mutex_lock(&(philo->value->is_alive_mutex));
		if (philo->value->is_alive == 0)
			return(pthread_mutex_unlock(&(philo->value->is_alive_mutex)), NULL);
		pthread_mutex_unlock(&(philo->value->is_alive_mutex));
		usleep (10);
	}
	return (NULL);
}
