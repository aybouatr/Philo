/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:20:19 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 22:20:22 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 250

typedef struct s_philo
{
	int				time_eat;
	pthread_t		threads;
	int				time_to_sleep;
	short			eating;
	short			id;
	int				nbr_eating;
	int				time_to_die;
	int				nbr_of_eat;
	int				num_philo;
	int				last_meal;
	int				start_time;
	int				*some_one_dead;
	pthread_mutex_t	*lock_print;
	pthread_mutex_t	*lock_dead;
	pthread_mutex_t	*lock_meal;
	pthread_mutex_t	*lock_fork_r;
	pthread_mutex_t	*lock_fork_l;

}					t_philo;

typedef struct s_meta_data
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nbr_of_eat;
	int				some_one_dead;
	int				num_philo;
	int				nbr_eating;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_meal;
	t_philo			*philo_s;
}					t_meta_data;

int					get_current_time(void);
int					ft_usleep(int milliseconds, t_philo *philo);
void				manage_threads(t_meta_data *meta_data,
						pthread_mutex_t *forks);
int					ft_digit(char c);
int					ft_is_all_digit(char *str);
int					ft_is_correct_nbr(char **av);
int					ft_atoi(char *str);
int					ft_check_range_between(char *str, int max, int min);
int					ft_is_correc_range(char **av);
int					ft_parsing(char **av);
void				init_meta(t_meta_data *data, t_philo *philoo, char **av);
void				init_forks(pthread_mutex_t *forks, int num_philo);
void				init_philo_s(t_meta_data *meta_data,
						pthread_mutex_t *forks);
int					ft_strlen(char *str);
int					is_live(t_philo *philo);
void				printf_message(char *str, t_philo *philo);
void				sleeping(t_philo *philo);
void				*minotor(void *info);
void				free_all(char *str, t_meta_data *meta_data,
						pthread_mutex_t *forks);
int					philo_is_late(t_philo *philo);
int					is_all_live(t_philo *philo_s);
int					is_all_ate(t_philo *philos);
void				*minotoring_all_threads(void *data);
void				manage_threads(t_meta_data *meta_data,
						pthread_mutex_t *forks);
void				performent_requement(char **av);
void				eat(t_philo *philo);
void get_corect_fork(t_meta_data* meta, pthread_mutex_t *forks,int j);

#endif
