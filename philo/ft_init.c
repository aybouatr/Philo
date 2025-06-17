/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:45:14 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:37 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_meta(t_meta_data *data, t_philo *philoo, char **av)
{
	pthread_mutex_init(&data->lock_print, NULL);
	pthread_mutex_init(&data->lock_dead, NULL);
	pthread_mutex_init(&data->lock_meal, NULL);
	data->nbr_eating = 0;
	data->some_one_dead = 0;
	data->philo_s = philoo;
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_die = ft_atoi(av[2]);
	data->num_philo = ft_atoi(av[1]);
	if (av[5] != NULL)
		data->nbr_of_eat = ft_atoi(av[5]);
	else
		data->nbr_of_eat = -1;
}

void	init_forks(pthread_mutex_t *forks, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philo_s(t_meta_data *meta,
					pthread_mutex_t *forks)
{
	int	j;

	j = -1;
	while (++j < meta->num_philo)
	{
		meta->philo_s[j].id = j + 1;
		meta->philo_s[j].last_meal = get_current_time();
		meta->philo_s[j].start_time = get_current_time();
		meta->philo_s[j].nbr_eating = 0;
		meta->philo_s[j].eating = 0;
		meta->philo_s[j].some_one_dead = &meta->some_one_dead;
		meta->philo_s[j].time_to_die = meta->time_to_die;
		meta->philo_s[j].time_eat = meta->time_to_eat;
		meta->philo_s[j].time_to_sleep = meta->time_to_sleep;
		meta->philo_s[j].lock_print = &meta->lock_print;
		meta->philo_s[j].lock_dead = &meta->lock_dead;
		meta->philo_s[j].lock_meal = &meta->lock_meal;
		meta->philo_s[j].num_philo = meta->num_philo;
		meta->philo_s[j].nbr_of_eat = meta->nbr_of_eat;
		get_corect_fork(meta,forks,j);
	}
}

int	ft_usleep(int milliseconds, t_philo *philo)
{
	int	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (is_live(philo))
			break ;
		usleep(500);
	}
	return (0);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
