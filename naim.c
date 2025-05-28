/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:25:11 by aybouatr          #+#    #+#             */
/*   Updated: 2025/04/13 11:25:37 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//-------> start parsing <-------------
pthread_mutex_t lock;

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
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
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int )res * sgn);
}

int len_arr(char** arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

t_arg_data inisilise_struct(char** av)
{
    int len;
    t_arg_data data;

    len = len_arr(av);
    data.nbr_philo = ft_atoi(av[1]);
    data.time_die = ft_atoi(av[2]);
    data.time_eat = ft_atoi(av[3]);
    data.time_sleep = ft_atoi(av[4]);
    if (len == 6)
        data.nbr_of_time_eat_for_philo = ft_atoi(av[5]);
    else
        data.nbr_of_time_eat_for_philo = -1;
    return (data);
}
 
size_t get_current_time()
{
    struct timeval time;
 
    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
 
void ft_usleep(size_t milisecound)
{
    size_t start;
 
    start = get_current_time();
    while ((get_current_time() - start) < milisecound)
        usleep(500);
    return;
    
}
// ------------------ list ----------

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
    lst->previous = NULL;
    lst->next = NULL;
	return (lst);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *current;

    if (!lst || !new)
        return ;
    current = *lst;
    if (!current)
    {
        new->previous = new;
        new->next = new;
        *lst = new;
        return ;
    }
    while (current->next != *lst)
        current = current->next;
    current->next = new;
    new->previous = current;
    new->next = *lst;
    (*lst)->previous = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	head -> content = content;
	head -> next = NULL;
    head -> previous = NULL;
	return (head);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*help;
    t_list  *last;

	if ((!lst))
		return ;
	help = *lst;
    last = help->previous;
	while (help != last)
	{
		temp = help;
		help = help->next;
		free(temp->content);
		free(temp);
	}
    free(last->content);
    free(last);
	*lst = NULL;
}

// ------------------end list---------------

// --------------- build garbge collector -----------------------

void gc_save_clean_memory(void *ptr,t_option option)
{
    static t_list* save_add;

    if(option == save)
        ft_lstadd_back(&save_add,ft_lstnew(ptr));
    else if (option == clean)
        ft_lstclear(&save_add);
}
void clean_memory(t_list* lst,int nb)
{
   ft_lstclear(&lst);
   exit(nb);
}

//----------------- end grbg collrctor --------------------

t_into_philo *inisilise_struct_for_philo(int id,t_arg_data info)
{
    t_into_philo *philo;

    philo = (t_into_philo *)malloc(sizeof(t_into_philo));
    if (philo == NULL)
        return (NULL);
    philo->id_philo = id;
    philo->status = thinking;
    pthread_mutex_init(&philo->fork_philo, NULL);
    philo->last_meal = 0;
    philo->time_die = info.time_die;
    philo->time_sleep = info.time_sleep;
    philo->time_thinking = info.time_thinking;
    philo->time_eat = info.time_eat;
    return (philo);
}

void destroy_all_mutex(t_list *lst_philo)
{
    t_into_philo *philo;
    t_list *temp;

    if (!lst_philo)
        return ;
    temp = lst_philo;
    while (temp != lst_philo->previous)
    {
        philo = (t_into_philo *)temp->content;
        pthread_mutex_destroy(&philo->fork_philo);
        temp = temp->next;
    }
    pthread_mutex_destroy(philo->lock);
    free(philo->lock);
}

void print_message(size_t time,t_into_philo** ph, const char *message)
{

    t_into_philo *philo;
    
    philo = *ph;
    printf("%lu\n",philo->id_philo);
    pthread_mutex_lock(philo->lock);
    *ph = philo;
    printf("%lu %lu %s\n", time, philo->id_philo, message);
    pthread_mutex_unlock(philo->lock);
    *ph = philo;
}

void check_is_late(t_into_philo *philo,t_list* lst, unsigned long time2)
{
    if ((get_current_time() - time2) > philo->time_die)
    {
        print_message(get_current_time() - time2, &philo, "is dead");
        destroy_all_mutex(lst);
        clean_memory(lst, -1);
    }
}

// void case_odd(t_list* lst,t_into_philo *current_philo, t_into_philo *next, size_t time, unsigned long *time2)
// {

//     pthread_mutex_lock(&current_philo->fork_philo);
//     print_message(get_current_time() - time, current_philo, "has taken fork");
//     pthread_mutex_lock(&next->fork_philo);

//     print_message(get_current_time() - time, current_philo, "has taken fork");
        
//     check_is_late(current_philo, lst,*time2);
//     print_message(get_current_time() - time, current_philo, "is eating");
           
//     print_message(get_current_time() - *time2, current_philo, "check time");

//     *time2 = get_current_time();
//     pthread_mutex_unlock(&next->fork_philo);
//     pthread_mutex_unlock(&current_philo->fork_philo);

// }
// void case_even(t_list* lst,t_into_philo *current_philo, t_into_philo *next, size_t time, unsigned long *time2)
// {
//     pthread_mutex_lock(&next->fork_philo);

//     print_message(get_current_time() - time, current_philo, "has taken fork");

//     pthread_mutex_lock(&current_philo->fork_philo);


//     check_is_late(current_philo,lst, *time2);
           
//     *time2 = get_current_time();
//     print_message(get_current_time() - time, current_philo, "has taken fork");
//     print_message(get_current_time() - time, current_philo, "is eating");
//     ft_usleep(current_philo->time_eat);
//     pthread_mutex_unlock(&current_philo->fork_philo);
//     pthread_mutex_unlock(&next->fork_philo);
// }

void *routine_philo(void *lst)
{
    t_into_philo *current_philo;
    t_into_philo *next;
    t_list       *lst_philo;
    size_t       time;
    unsigned long time2;
    int i;

    lst_philo = (t_list *)lst;
    current_philo = (t_into_philo *)lst_philo->content;
    next = (t_into_philo *)lst_philo->next->content;
    time = get_current_time();
    time2 = get_current_time();
    i = 0;
    while (1)
    {
        if (current_philo->id_philo % 2 == 0)
        {
            //case_even(lst,current_philo, next, time, &time2); 

            pthread_mutex_lock(&next->fork_philo);

            print_message(get_current_time() - time, &current_philo, "has taken fork");

            pthread_mutex_lock(&current_philo->fork_philo);
            check_is_late(current_philo,lst, time2);

            time2 = get_current_time();
           
            print_message(get_current_time() - time, &current_philo, "has taken fork");
            print_message(get_current_time() - time, &current_philo, "is eating");
          //  ft_usleep(1000 * current_philo->time_eat);
            pthread_mutex_unlock(&current_philo->fork_philo);
            pthread_mutex_unlock(&next->fork_philo);
    
        }
        else 
        {
            //case_odd(lst_philo,current_philo, next, time, &time2);
            pthread_mutex_lock(&current_philo->fork_philo);
            print_message(get_current_time() - time, &current_philo, "has taken fork");
            pthread_mutex_lock(&next->fork_philo);

            print_message(get_current_time() - time, &current_philo, "has taken fork");
        
             check_is_late(current_philo, lst,time2);
            print_message(get_current_time() - time, &current_philo, "is eating");
           
            time2 = get_current_time();

            pthread_mutex_unlock(&next->fork_philo);
            pthread_mutex_unlock(&current_philo->fork_philo);
        }

        ft_usleep(10 * current_philo->time_eat);

        print_message(get_current_time() - time, &current_philo, "is sleeping");

        ft_usleep(10 * current_philo->time_sleep);

        print_message(get_current_time() - time, &current_philo, "is thinking");

        ft_usleep(10);    
        
        i++;
    }
    return NULL;
}


void performent_philosopher(t_list* lst_philo)
{
    int i;
    t_into_philo* philo;
    t_into_philo* temp;

    i = 0;
    philo = (t_into_philo* )lst_philo->previous->content;
    while (philo && i < philo->id_philo)
    {
        temp = (t_into_philo *)lst_philo->content;
        if (pthread_create(&temp->threads,NULL,&routine_philo,(void *)lst_philo))
        {
            perror("faild creat thread \n");
            exit(-1);
        }
        //ft_usleep(10);
        temp = NULL;
        lst_philo = lst_philo->next;
        i++;
    }
    i = 0;
    while (philo && i < philo->id_philo)
    {
        temp = (t_into_philo *)lst_philo->content;
        pthread_join(temp->threads, NULL);
        lst_philo = lst_philo->next;
        i++;
    }
    
    printf("all philosophers have finished their routine\n");
}

void error()
{
    printf("error in malloc\n");
    exit(-1);
}

t_list*  init(char ** av)
{
    int i;
    t_into_philo *philo;
    t_list       *lst_philo;
    pthread_mutex_t *lock;
    t_arg_data data;
    data = inisilise_struct(av);

    lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (lock == NULL)
        error();
    pthread_mutex_init(lock, NULL);   
    i = 1;
    lst_philo = NULL;
    while (i <= data.nbr_philo)
    {
        philo = inisilise_struct_for_philo(i,data);
        if (philo == NULL)
            clean_memory(lst_philo,-1);
        philo->lock = lock;
        ft_lstadd_back(&lst_philo,ft_lstnew((void *)philo));
        philo = NULL;
        i++;
    }
    return (lst_philo);
}

int parsig_arg(char** av)
{
    int i;
    int index;

    index = 1;
    while (av && av[index])
    {
        i = 0;
        while (av[index] && av[index][i] != '\0')
        {
            if (!ft_isdigit(av[index][i]))
                return (-1);
            i++;
        }
        index++;
    }
    return (0);
}

int ft_philo(char** av)
{
    t_list *lst_philo;
    t_arg_data data_philos;

    if (parsig_arg(av) == -1)
        return (-1);
    lst_philo = init(av);
    performent_philosopher(lst_philo);
    return (0);
}

//-----------> end parsing <----------

int main(int ac, char **av)
{
    // int ac;
    // char **av;

    // ac = 7;
    // av = (char **)malloc(sizeof(char *) * ac);
    // av[0] = "philo";
    // av[1] = "2";
    // av[2] = "80";
    // av[3] = "20";
    // av[4] = "20";
    // av[5] = "7";
    // av[6] = NULL;
    if (ac < 6)
    {
        printf("you shouls argument like this : number_of_philosophers time_to_die time_to_eat ");
        printf("time_to_sleep [number_of_times_each_philosopher_must_eat]");
    }
    else if (ft_philo(av) == -1)
    {
        printf("fix argument !\n");
    }
    return 0;
}