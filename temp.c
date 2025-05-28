void case_odd(t_list* lst,t_into_philo **current_philo, t_into_philo **next, size_t time, unsigned long *time2)
{
    t_into_philo *temp_next;
    t_into_philo *temp_current;

    temp_next = *next;
    temp_current = *current_philo;
    pthread_mutex_lock(&temp_current->fork_philo);
    print_message(get_current_time() - time, temp_current, "has taken fork");
    pthread_mutex_lock(&temp_next->fork_philo);

    print_message(get_current_time() - time, temp_current, "has taken fork");
        
    check_is_late(temp_current, lst,*time2);
    print_message(get_current_time() - time, temp_current, "is eating");
    ft_usleep(temp_current->time_eat);
    //print_message(get_current_time() - *time2, temp_current, "check time");

    *time2 = get_current_time();
    pthread_mutex_unlock(&temp_next->fork_philo);
    pthread_mutex_unlock(&temp_current->fork_philo);

    *current_philo = temp_next;
    *next = temp_next;

}
void case_even(t_list* lst,t_into_philo **current_philo, t_into_philo **next, size_t time, unsigned long *time2)
{
    t_into_philo *temp_next;
    t_into_philo *temp_current;

    temp_next = *next;
    temp_current = *current_philo;

    pthread_mutex_lock(&temp_next->fork_philo);

    print_message(get_current_time() - time, temp_current, "has taken fork");

    pthread_mutex_lock(&temp_current->fork_philo);


    check_is_late(temp_current,lst, *time2);
           
    *time2 = get_current_time();
    print_message(get_current_time() - time, temp_current, "has taken fork");
    print_message(get_current_time() - time, temp_current, "is eating");
    ft_usleep(temp_current->time_eat);
    pthread_mutex_unlock(&temp_current->fork_philo);
    pthread_mutex_unlock(&temp_next->fork_philo);

    *current_philo = temp_next;
    *next = temp_next;
}