#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>

#define MAX_PHILO 250


typedef struct s_philo
{
    size_t time_eat;
    pthread_t threads;
    size_t time_sleep;
    short eating;
    short id;
    size_t nbr_eating;
    size_t time_to_die;
    size_t nbr_of_eat;
    size_t num_philo;
    size_t last_meal;
    size_t start_time;
    size_t *some_one_dead;
    pthread_mutex_t *lock_print;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t* lock_meal;
    pthread_mutex_t *lock_fork_r;
    pthread_mutex_t *lock_fork_l;

}   t_philo;



typedef struct s_meta_data
{
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t time_to_die;
    size_t nbr_of_eat;
    size_t some_one_dead;
    size_t num_philo;
    size_t nbr_eating;
    pthread_mutex_t lock_print;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_meal;
    t_philo* philo_s;
}   t_meta_data;

size_t	get_current_time(void);
int	    ft_usleep(size_t milliseconds);
void manage_threads(t_meta_data* meta_data,pthread_mutex_t* forks);
int ft_digit(char c);
int ft_is_all_digit(char* str);
int ft_is_correct_nbr(char** av);
unsigned long ft_atoi(char* str);
int ft_check_range_between(char* str,size_t max,size_t min);
int ft_is_correc_range(char** av);
int ft_parsing(char** av);

void init_meta(t_meta_data* data,t_philo* philoo,char** av);
void init_forks(pthread_mutex_t *forks,size_t num_philo);
void init_philo_s(t_philo* philo_s,t_meta_data* meta_data,pthread_mutex_t* forks);

int	ft_strlen(char *str);
int is_live(t_philo* philo);
void printf_message(char* str,t_philo* philo);
void eat(t_philo* philo);
void sleeping(t_philo* philo);
void *minotor(void* info);
void free_all(char* str,t_meta_data* meta_data,pthread_mutex_t* forks);
int philo_is_late(t_philo* philo);
int is_all_live(t_philo* philo_s);
int is_all_ate(t_philo* philos);
void    *minotoring_all_threads(void* data);
void manage_threads(t_meta_data* meta_data,pthread_mutex_t* forks);
void performent_requement(char ** av);



# endif 



#include "philo.h"


int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Gets the current time in milliseconds

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// ---------------- start parsing -----------------

int ft_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_is_all_digit(char* str)
{
    int i;
    // int check_1;
    // int check_2;

    i = 0;
    while (str[i])
    {
        if (!ft_digit(str[i]) && (!((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')))
            return (1);
        
        i++;
    }
    return (0);
}

int ft_is_correct_nbr(char** av)
{
    int i;

    i = 1;
    while (av[i])
    {
        if (ft_is_all_digit(av[i]))
            return (1);
        i++;
    }
    return (0);
}

unsigned long ft_atoi(char* str)
{
   unsigned long	res;
	size_t	i;
	int		sgn;

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

int ft_check_range_between(char* str,size_t max,size_t min)
{
   if (ft_atoi(str) > max || min > ft_atoi(str))
        return (1);
    return (0);
}

int ft_is_correc_range(char** av)
{
    int e;

    e = 1;
    while (av[e])
    {
        if (ft_check_range_between(av[e],SIZE_MAX,1))
            return (1);
        e++;
    }
    if (ft_check_range_between(av[1],MAX_PHILO,1))
            return (1);
    return (0);
}

int ft_parsing(char** av)
{
    if (ft_is_correct_nbr(av) || ft_is_correc_range(av))
        return (1);
    return (0);
}

// ---------------- end parsing -------------------

// [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
// [number_of_times_each_philosopher_must_eat]

// --------------- init variable ------------------

void init_meta(t_meta_data* data,t_philo* philoo,char** av)
{
    pthread_mutex_init(&data->lock_print,NULL);
    pthread_mutex_init(&data->lock_dead,NULL);
    pthread_mutex_init(&data->lock_meal,NULL);
    data->nbr_eating = 0;
    data->some_one_dead = 0;
    data->philo_s = philoo;
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep= ft_atoi(av[4]);
    data->time_to_die = ft_atoi(av[2]);
    data->num_philo = ft_atoi(av[1]);
    if (av[5] != NULL)
        data->nbr_of_eat = ft_atoi(av[5]);
    else
        data->nbr_of_eat = -1;
}

void init_forks(pthread_mutex_t *forks,size_t num_philo)
{
    int i;

    i = 0;
    while (i < num_philo)
    {
        pthread_mutex_init(&forks[i],NULL);
        i++;
    }
}

void init_philo_s(t_philo* philo_s,t_meta_data* meta_data,pthread_mutex_t* forks)
{
    int j;

    j = 0;
    while (j < meta_data->num_philo)
    {
        meta_data->philo_s[j].id = j + 1;
        meta_data->philo_s[j].last_meal = get_current_time();
        meta_data->philo_s[j].start_time = get_current_time();
        meta_data->philo_s[j].nbr_eating = 0;
        meta_data->philo_s[j].eating = 0;
        meta_data->philo_s[j].some_one_dead = &meta_data->some_one_dead;
        meta_data->philo_s[j].time_to_die = meta_data->time_to_die;
        meta_data->philo_s[j].time_eat = meta_data->time_to_eat;
        meta_data->philo_s[j].time_sleep = meta_data->time_to_sleep;
        meta_data->philo_s[j].lock_print = &meta_data->lock_print;
        meta_data->philo_s[j].lock_dead = &meta_data->lock_dead;
        meta_data->philo_s[j].lock_meal= &meta_data->lock_meal;
        meta_data->philo_s[j].num_philo = meta_data->num_philo;
        meta_data->philo_s[j].nbr_of_eat = meta_data->nbr_of_eat;
        meta_data->philo_s[j].lock_fork_l = &forks[j];
        if (j == 0)
            meta_data->philo_s[j].lock_fork_r = &forks[meta_data->num_philo - 1];
        else
           meta_data->philo_s[j].lock_fork_r = &forks[j - 1];
        j++;
    }
    
}

// ---------------- end init var ------------------

// ---------------- start requrement  -------------------

// void *minotoring_all_threads(void* philo_s)
// {

// }

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

int is_live(t_philo* philo)
{
    pthread_mutex_lock(philo->lock_dead);
    if (*philo->some_one_dead == 1)
        return (pthread_mutex_unlock(philo->lock_dead),1);
    pthread_mutex_unlock(philo->lock_dead);
    return (0);
}

void printf_message(char* str,t_philo* philo)
{
    size_t time;

    pthread_mutex_lock(philo->lock_print);
    time = get_current_time() - philo->start_time;
    if (!is_live(philo))
       printf("%zu %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(philo->lock_print);
}

void eat_l(t_philo* philo)
{
    pthread_mutex_lock(philo->lock_fork_l);
	printf_message("has taken a fork", philo);
    // if (philo->num_philo == 1)
	// {
	// 	ft_usleep(philo->time_to_die);
	// 	pthread_mutex_unlock(philo->lock_fork_r);
	// 	return ;
	// }
	pthread_mutex_lock(philo->lock_fork_r);
	printf_message("has taken a fork", philo);
	philo->eating = 1;
	printf_message("is eating", philo);
	pthread_mutex_lock(philo->lock_meal);
	philo->last_meal = get_current_time();
	philo->nbr_eating++;
	pthread_mutex_unlock(philo->lock_meal);
	ft_usleep(philo->time_eat);
	philo->eating = 0;
    
	pthread_mutex_unlock(philo->lock_fork_r);
	pthread_mutex_unlock(philo->lock_fork_l);
}

void eat(t_philo* philo)
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

void sleeping(t_philo* philo)
{
    printf_message("is sleeping", philo);
	ft_usleep(philo->time_sleep);
}

void *minotor(void* info)
{
    t_philo* philo;

    philo = (t_philo* )info;
    if (philo->id % 2 == 0)
            ft_usleep(1);
    while (!is_live(philo))
    {
        // if (philo->id % 2 == 1)
        //     eat_r(philo);
        // else
        //     eat_l(philo);
        eat(philo);
        sleeping(philo);
        printf_message("is thinking",philo);
    }
    return (philo);
}

void free_all(char* str,t_meta_data* meta_data,pthread_mutex_t* forks)
{
    int i;

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

int philo_is_late(t_philo* philo)
{
    pthread_mutex_lock(philo->lock_meal);
	if (get_current_time() - philo->last_meal >= philo->time_to_die
        && philo->eating == 0)
		return (pthread_mutex_unlock(philo->lock_meal), 1);
	pthread_mutex_unlock(philo->lock_meal);
	return (0);
}

int is_all_live(t_philo* philo_s)
{
    int i;

    i = 0;
    while (i < philo_s[0].num_philo)
    {
        if (philo_is_late(&philo_s[i]))
        {
            printf_message("died",&philo_s[i]);
            pthread_mutex_lock(philo_s[i].lock_dead);
            *philo_s[i].some_one_dead = 1;
            pthread_mutex_unlock(philo_s[i].lock_dead);
            return (1);
        }      
        i++;
    }
    return (0);
    
}

int is_all_ate(t_philo* philos)
{
    int i;
    size_t is_max_ate;
    
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

void    *minotoring_all_threads(void* data)
{
    t_philo* philo_s;

    philo_s = (t_philo *)data;
    while (1337)
    {
        if (is_all_live(philo_s) == 1 || is_all_ate(philo_s) == 1)
            break;
    }
    return (data);
}

void manage_threads(t_meta_data* meta_data,pthread_mutex_t* forks)
{
    int i;
    pthread_t threads;

    i = 0;
    if (pthread_create(&threads,NULL,&minotoring_all_threads,meta_data->philo_s) != 0)
        free_all("faild creat thread ",meta_data,forks);
    while (i < meta_data->philo_s[0].num_philo)
    {
        if (pthread_create(&meta_data->philo_s[i].threads,NULL,&minotor,&meta_data->philo_s[i]) != 0)
            free_all("faild creat thread ",meta_data,forks);
        i++;
    }    
    if (pthread_join(threads,NULL) != 0)
        free_all("faild creat thread ",meta_data,forks);
    i = 0;
    while (i < meta_data->philo_s[0].num_philo)
    {
        if (pthread_join(meta_data->philo_s[i].threads,NULL) != 0)
            free_all("faild creat thread ",meta_data,forks);
        i++;
    }
}

void performent_requement(char ** av)
{
    pthread_mutex_t forks[MAX_PHILO];
    t_philo         philo_s[MAX_PHILO];
    t_meta_data     meta;

    init_meta(&meta,philo_s,av);
    init_forks(forks,meta.num_philo);
    init_philo_s(philo_s,&meta,forks);
    manage_threads(&meta,forks);
    free_all(NULL,&meta,forks);
}

// ---------------- end requrement  -------------------


int main(int ac,char** av)
{
    if (ac == 6 || ac == 5)
    {
        if(ft_parsing(av))
            printf("fix content argument \n");
        else
            performent_requement(av);
    }
    else
        printf("fix argument \n");
}
