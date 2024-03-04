/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:17:45 by smarty            #+#    #+#             */
/*   Updated: 2024/03/04 19:05:26 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_list
{
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int target;
}           t_list;

typedef struct s_philo
{
    int				number;
	long long		last_eat;
	int             n_eat;
    pthread_t  id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*eaten;
	pthread_mutex_t	*time_last_eat;
    t_list          *value; 
}               t_philo;

int			ft_atoi(char *nptr);
long long   timecode(void);
void    *daily(void *arg);
int    init_philo(t_list *meal);


# endif
