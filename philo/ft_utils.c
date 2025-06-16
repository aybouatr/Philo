/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:16:55 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 22:16:57 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_l(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_fork_l);
	printf_message("has taken a fork", philo);
	pthread_mutex_lock(philo->lock_fork_r);
	printf_message("has taken a fork", philo);
	philo->eating = 1;
	printf_message("is eating", philo);
	pthread_mutex_lock(philo->lock_meal);
	philo->last_meal = get_current_time();
	philo->nbr_eating++;
	pthread_mutex_unlock(philo->lock_meal);
	ft_usleep(philo->time_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->lock_fork_l);
	pthread_mutex_unlock(philo->lock_fork_r);
}


int	ft_atoi(char *str)
{
	int	res;
	int	i;
	int	sgn;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	sgn = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	res = 0;
	while (str[i] && ft_digit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sgn);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	sleeping(t_philo *philo)
{
	printf_message("is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

int	is_live(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	if (*philo->some_one_dead == 1)
	{
		pthread_mutex_unlock(philo->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_dead);
	return (0);
}
