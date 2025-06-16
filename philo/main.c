/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:57:38 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 21:57:42 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 6 || ac == 5)
	{
		if (ft_parsing(av))
			printf("fix content argument \n");
		else
			performent_requement(av);
	}
	else
		printf("fix argument \n");
	return (0);
}
