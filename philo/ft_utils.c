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

void get_corect_fork(t_meta_data* meta, pthread_mutex_t *forks,int j)
{
	if (j % 2 == 0)
	{
		meta->philo_s[j].lock_fork_l = &forks[j];
		if (j == 0)
			meta->philo_s[j].lock_fork_r = &forks[meta->num_philo - 1];
		else
			meta->philo_s[j].lock_fork_r = &forks[j - 1];
	}
	else
	{
		meta->philo_s[j].lock_fork_r = &forks[j];
		if (j == 0)
			meta->philo_s[j].lock_fork_l = &forks[meta->num_philo - 1];
		else
			meta->philo_s[j].lock_fork_l = &forks[j - 1];
	}
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
