/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:45:48 by aybouatr          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:52 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_digit(str[i]) && (!((str[i] >= 9 && str[i] <= 13)
					|| str[i] == ' ')))
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_correct_nbr(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_is_all_digit(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_range_between(char *str, int max, int min)
{
	if (ft_atoi(str) > max || min > ft_atoi(str))
		return (1);
	return (0);
}

int	ft_is_correc_range(char **av)
{
	int	e;

	e = 1;
	while (av[e])
	{
		if (ft_check_range_between(av[e], INT_MAX, 1))
			return (1);
		e++;
	}
	if (ft_check_range_between(av[1], MAX_PHILO, 1))
		return (1);
	return (0);
}

int	ft_parsing(char **av)
{
	if (ft_is_correct_nbr(av) || ft_is_correc_range(av))
		return (1);
	return (0);
}
