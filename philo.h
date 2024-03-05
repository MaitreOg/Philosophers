/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:17:45 by smarty            #+#    #+#             */
/*   Updated: 2024/03/05 20:24:54 by smarty           ###   ########.fr       */
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
    int t_day;
    int target;
    int in_process;
    pthread_mutex_t mutex_in_process;
	pthread_mutex_t	*fork;
}           t_list;

typedef struct s_philo
{
    int				number;
	long long		last_eat;
	int             n_eat;
    pthread_t  id;
	pthread_mutex_t	eaten;
	pthread_mutex_t	time_last_eat;
    t_list          *value; 
}               t_philo;

int			ft_atoi(char *nptr);
long long   timecode(void);
void    *daily(void *arg);
int    init_philo(t_list *meal);
int		init_meal(int ac, char **av);
void	end_thread(t_philo *philo, int i);
# endif
