/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:28:10 by smarty            #+#    #+#             */
/*   Updated: 2024/03/11 18:27:08 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(philo->value->fork[r_fork]));
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->value->fork[l_fork]));
	print_status(philo, "has taken a fork");
	
}

void	eat(t_philo *philo, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(philo->eaten));
	philo->n_eat += 1;
	philo->last_eat = timecode();
	print_status(philo, "is eating");
	pthread_mutex_unlock(&(philo->eaten));
	pthread_mutex_lock(&(philo->time_last_eat));
	philo->last_eat = timecode();
	pthread_mutex_unlock(&(philo->time_last_eat));
	pthread_mutex_unlock(&(philo->value->routine));
    wait_next(philo->value->t_eat);
	pthread_mutex_unlock(&(philo->value->fork[r_fork]));
	pthread_mutex_unlock(&(philo->value->fork[l_fork]));
}

void	bed(t_philo	*philo)
{
	print_status(philo, "is sleeping");
    wait_next(philo->value->t_sleep);
	print_status(philo, "is thinking");

}