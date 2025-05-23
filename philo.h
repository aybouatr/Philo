/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:24:08 by aybouatr          #+#    #+#             */
/*   Updated: 2025/04/13 11:24:11 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct arg_data
{
    unsigned long nbr_philo;
    unsigned long time_die;
    unsigned long time_eat;
    unsigned long  time_thinking;
    unsigned long time_sleep;
    unsigned long nbr_of_time_eat_for_philo;
    
}t_arg_data;

// typedef enum status_philo
// {
//     thinking,
//     sleeping,
//     eating,

// }e_status_philo;

typedef enum s_option
{
    save,
    clean,
}t_option;


typedef struct info_philo
{
    pthread_t       threads;
    pthread_mutex_t fork_philo;
    unsigned long   last_meal;
    unsigned long   time_die;
    unsigned long   time_thinking;
    unsigned long   time_eat;
    unsigned long   time_sleep;
    unsigned long   id_philo;

}t_into_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
    struct s_list   *previous;
}	t_list;

void gc_save_clean_memory(void *ptr,t_option option);

# endif
