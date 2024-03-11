/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:17:45 by smarty            #+#    #+#             */
/*   Updated: 2024/03/11 18:26:18 by smarty           ###   ########.fr       */
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
    long long   time_lunch;
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int t_day;
    int target;
    int is_alive;
    int stop_meal;
    pthread_mutex_t is_alive_mutex;
    pthread_mutex_t routine;
    pthread_mutex_t mutex_stop;
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
void    init_philo(t_list *meal);
int		init_meal(int ac, char **av);
void	end_thread(t_philo *philo, int i);
void    take_forks(t_philo *philo, int l_fork, int r_fork);
void	eat(t_philo *philo, int l_fork, int r_fork);
void	bed(t_philo	*philo);
void	print_status(t_philo *philo, char *status);
void	alive_and_hungry(t_philo  *philo);
void	print_eat(t_philo *philo, char *status, long long time);
void	wait_next(int target);
# endif
