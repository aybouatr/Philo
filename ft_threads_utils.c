/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:46:32 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 21:46:45 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_message(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->lock_print);
	time = get_current_time() - philo->start_time;
	if (!is_live(philo))
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->lock_print);
}

void	free_all(char *str, t_meta_data *meta_data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	while (i < meta_data->num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&meta_data->lock_dead);
	pthread_mutex_destroy(&meta_data->lock_print);
}

int	philo_is_late(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_meal);
	if (get_current_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->lock_meal), 1);
	pthread_mutex_unlock(philo->lock_meal);
	return (0);
}

int	is_all_live(t_philo *philo_s)
{
	int	i;

	i = 0;
	while (i < philo_s[0].num_philo)
	{
		if (philo_is_late(&philo_s[i]))
		{
			printf_message("died", &philo_s[i]);
			pthread_mutex_lock(philo_s[i].lock_dead);
			*philo_s[i].some_one_dead = 1;
			pthread_mutex_unlock(philo_s[i].lock_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_all_ate(t_philo *philos)
{
	int	i;
	int	is_max_ate;

	i = 0;
	is_max_ate = 0;
	if (philos[0].nbr_of_eat == -1)
		return (0);
	while (i < philos[0].num_philo)
	{
		pthread_mutex_lock(philos[i].lock_meal);
		if (philos[i].nbr_eating >= philos[i].nbr_of_eat)
			is_max_ate++;
		pthread_mutex_unlock(philos[i].lock_meal);
		i++;
	}
	if (is_max_ate == philos[0].num_philo)
	{
		pthread_mutex_lock(philos[0].lock_dead);
		*philos->some_one_dead = 1;
		pthread_mutex_unlock(philos[0].lock_dead);
		return (1);
	}
	return (0);
}
