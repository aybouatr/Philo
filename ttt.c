#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

// -------------------- start declare staructures and macro and enum --------------------

typedef struct arg_data
{
    long nbr_philo;
    long time_die;
    long time_eat;
    long time_sleep;
    long nbr_of_time_eat_for_philo;
    
}t_arg_data;

typedef struct info_philo
{
    int             used_fork;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             id_philo;

}t_into_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
    struct s_list   *previous;
}	t_list;


//------------------------- end defination  struct ----------------------

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

	head = (t_list *)malloc (sizeof(t_list));
	if (!head)
		return (NULL);
	head -> content = content;
	head -> next = NULL;
    head -> previous = NULL;
	return (head);
}

uint64_t get_current_time(void)
{
    struct timeval time;
    uint64_t milliseconds;

    if (gettimeofday(&time, NULL) == -1) {
        write(2, "gettimeofday() error\n", 22);
        return 0;
    }
    milliseconds = (uint64_t)time.tv_sec * 1000 + time.tv_usec / 1000;
    return (milliseconds);
}


void ft_usleep(size_t milisecound)
{
    size_t start;

    start = get_current_time();
    while ((get_current_time() - start) < milisecound)
        usleep(500);
    return ;
    
}

int main()
{

    

}
