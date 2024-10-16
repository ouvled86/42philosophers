/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/16 11:57:25 by ouel-bou         ###   ########.fr       */
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
		if (philos[i].meals_eaten < meals_num)
			ret = false;
		i++;
	}
	return (ret);
}

int	philo_is_dead(t_philo *philos, t_clock *clock, int count)
{
	int		ret;
	int		i;

	ret = -1;
	i = 0;
	while (i < count)
	{
		if (philos[i].full == true)
			i++;
		if (philos[i].last_meal != -1)
		{
			if (get_time() - philos[i].last_meal >= clock->t_to_die)
				ret = i + 1;
		}
		else
		{
			if (get_time() - clock->start_time >= clock->t_to_die)
				ret = i + 1;
		}
		i++;
	}
	return (ret);
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
			set_bool(&data->table, &data->dead_flag, true);
			break ;
		}
		dead_philo = philo_is_dead(data->philos, data->clock, data->philos_num);
		if (dead_philo >= 0)
		{
			set_bool(&data->table, &data->dead_flag, true);
			print_status(dead_philo + 1, DEAD, data->clock->start_time);
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
		philo_handle(data->philos, CREATE, i);
		i++;
	}
	i = 0;
	set_num(&data->table, &data->clock->start_time, get_time());
	printf("Start time: %ld\n", data->clock->start_time);
	set_bool(&data->table, &data->start_flag, true);
	while (i < data->philos_num)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
