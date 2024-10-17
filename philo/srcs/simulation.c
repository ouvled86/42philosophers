/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/17 16:10:13 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_meals(t_philo *philos, int meals_num, int count)
{
	bool	ret;
	int		i;

	ret = true;
	i = 0;
	while (i < count)
	{
		if (philos[i].meals_eaten < meals_num)
			ret = false;
		i++;
	}
	return (ret);
}

static int	philo_is_dead(t_philo *philos, t_clock *clock, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (philos[i].full == true && i + 1 < count)
			i++;
		if (philos[i].last_meal != -1)
		{
			if (get_time() - philos[i].last_meal >= clock->t_to_die)
				return (i + 1);
		}
		i++;
	}
	return (-1);
}

void	monitor_dinner(t_table *data)
{
	int	dead_philo;

	dead_philo = -1;
	while (86)
	{
		if (data->meals_num != -1 
			&& check_meals(data->philos, data->meals_num, data->philos_num))
		{
			set_bool(&data->table, &data->finish_flag, true);
			break ;
		}
		dead_philo = philo_is_dead(data->philos, data->clock, data->philos_num);
		if (dead_philo >= 0)
		{
			set_bool(&data->table, &data->dead_flag, true);
			print_status(dead_philo, DEAD, data->clock->start_time, 
				data);
			break ;
		}
	}
}

void	launch_dinner(t_table *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, 
				&data->philos[i]))
			err_exit(19, "philosophers: pthread_create failed!\n");
		i++;
	}
	i = 0;
	set_num(&data->table, &data->clock->start_time, get_time());
	set_bool(&data->table, &data->start_flag, true);
	while (i < data->philos_num)
	{
		if (pthread_detach(data->philos[i].thread))
			err_exit(23, "philosophers: pthread_detach failed!\n");
		i++;
	}
}
