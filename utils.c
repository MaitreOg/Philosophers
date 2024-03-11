/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarty <smarty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:49:41 by smarty            #+#    #+#             */
/*   Updated: 2024/03/11 18:25:47 by smarty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long   timecode(void)
{
    struct timeval  tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	wait_next(int target)
{
	long long	time;

	time = timecode();
	while (1)
	{
		if (timecode() - time >= target)
			break;
	}
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	result;
	int	signe;

	signe = 1;
	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * signe);
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	time = timecode() - philo->value->time_lunch;
	printf("%lld %d %s\n", time, philo->number, status);
}

void	print_eat(t_philo *philo, char *status, long long time)
{
	long long	time_p;

	time_p = time - philo->value->time_lunch;
	printf("%lld %d %s\n", time_p, philo->number, status);
}