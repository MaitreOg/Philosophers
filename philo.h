/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:17:45 by smarty            #+#    #+#             */
/*   Updated: 2024/03/19 19:45:41 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_list
{
	long long		time_lunch;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_day;
	int				target;
	int				is_alive;
	int				is_alive_txt;
	int				stop_meal;
	pthread_mutex_t	is_alive_mutex;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eaten;
	pthread_mutex_t	time_last_eat;
}		t_list;

typedef struct s_philo
{
	int				number;
	long long		last_eat;
	int				n_eat;
	pthread_t		id;
	t_list			*value;
}		t_philo;

int			ft_atoi(char *nptr);
long long	timecode(void);
void		*daily(void *arg);
void		init_philo(t_list *meal);
void		init_meal(int ac, char **av);
void		end_thread(t_philo *philo);
int			take_forks(t_philo *philo, int l_fork, int r_fork);
void		eat(t_philo *philo, int l_fork, int r_fork);
int			bed(t_philo	*philo);
void		print_status(t_philo *philo, char *status);
void		alive_and_hungry(t_philo *philo);
void		wait_next(int target);
void		dead(t_philo *philo);
void		one_philo(t_list *meal);
#endif
