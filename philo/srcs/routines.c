/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:56:25 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/10 11:57:13 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_meals(t_philo *philos, int meals_num, int count)
{
	bool	ret;
	int		i;

	ret = true;
	i = 0;
	while (i < count)
	{
		if (philos->meals_eaten < meals_num)
			ret = false;
		i++;
	}
	return (ret);
}

void	*monitor_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (86)
	{
		if (table->dead_flag)
			break ;
		if (table->meals_num != -1 
			&& check_meals(table->philos, table->meals_num, table->philos_num))
			break ;
	}
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	t_mutex	*mutex;

	philo = (t_philo *)data;
	table = philo->table;
}