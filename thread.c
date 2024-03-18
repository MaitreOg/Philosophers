/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:28:10 by smarty            #+#    #+#             */
/*   Updated: 2024/03/18 21:50:49 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo, int l_fork, int r_fork)
{
	if (philo->number % 2 == 0)
	{
		pthread_mutex_lock(&(philo->value->fork[r_fork]));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->value->fork[l_fork]));
		print_status(philo, "has taken a fork");
		return (1);
	}
	else
	{
		pthread_mutex_lock(&(philo->value->fork[l_fork]));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->value->fork[r_fork]));
		print_status(philo, "has taken a fork");
		return (1);
	}
}

void	eat(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(philo->value->eaten));
	philo->n_eat += 1;
	print_status(philo, "is eating");
	pthread_mutex_unlock(&(philo->value->eaten));
	pthread_mutex_lock(&(philo->value->time_last_eat));
	philo->last_eat = timecode();
	pthread_mutex_unlock(&(philo->value->time_last_eat));
	wait_next(philo->value->t_eat);
	if (philo->number % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->value->fork[l_fork]));
		pthread_mutex_unlock(&(philo->value->fork[r_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->value->fork[r_fork]));
		pthread_mutex_unlock(&(philo->value->fork[l_fork]));
	}
}

int	bed(t_philo	*philo)
{		
	print_status(philo, "is sleeping");
	wait_next(philo->value->t_sleep);
	print_status(philo, "is thinking");
	return (1);
}

void	dead(t_philo *philo)
{
	print_status(philo, "is dead");
	pthread_mutex_lock(&philo->value->is_alive_mutex);
	philo->value->is_alive = 0;
	philo->value->is_alive_txt = 0;
	pthread_mutex_unlock(&philo->value->is_alive_mutex);
}
