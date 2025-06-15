/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:46:20 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 21:46:22 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_fork_r);
	printf_message("has taken a fork", philo);
	if (philo->num_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->lock_fork_r);
		return ;
	}
	pthread_mutex_lock(philo->lock_fork_l);
	printf_message("has taken a fork", philo);
	philo->eating = 1;
	printf_message("is eating", philo);
	pthread_mutex_lock(philo->lock_meal);
	philo->last_meal = get_current_time();
	philo->nbr_eating++;
	pthread_mutex_unlock(philo->lock_meal);
	ft_usleep(philo->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->lock_fork_l);
	pthread_mutex_unlock(philo->lock_fork_r);
}

void	*minotor(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_live(philo))
	{
		eat(philo);
		sleeping(philo);
		printf_message("is thinking", philo);
	}
	return (philo);
}

void	*minotoring_all_threads(void *data)
{
	t_philo	*philo_s;

	philo_s = (t_philo *)data;
	while (1337)
	{
		if (is_all_live(philo_s) == 1 || is_all_ate(philo_s) == 1)
			break ;
	}
	return (data);
}

void	manage_threads(t_meta_data *meta_data, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	threads;

	i = 0;
	if (pthread_create(&threads, NULL, &minotoring_all_threads,
			meta_data->philo_s) != 0)
		free_all("faild creat thread ", meta_data, forks);
	while (i < meta_data->philo_s[0].num_philo)
	{
		if (pthread_create(&meta_data->philo_s[i].threads, NULL, &minotor,
				&meta_data->philo_s[i]) != 0)
			free_all("faild creat thread ", meta_data, forks);
		i++;
	}
	if (pthread_join(threads, NULL) != 0)
		free_all("faild creat thread ", meta_data, forks);
	i = 0;
	while (i < meta_data->philo_s[0].num_philo)
	{
		if (pthread_join(meta_data->philo_s[i].threads, NULL) != 0)
			free_all("faild creat thread ", meta_data, forks);
		i++;
	}
}

void	performent_requement(char **av)
{
	pthread_mutex_t	forks[MAX_PHILO];
	t_philo			philo_s[MAX_PHILO];
	t_meta_data		meta;

	init_meta(&meta, philo_s, av);
	init_forks(forks, meta.num_philo);
	init_philo_s(&meta, forks);
	manage_threads(&meta, forks);
	free_all(NULL, &meta, forks);
}
