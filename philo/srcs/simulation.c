/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/15 16:24:17 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	while (86)
	{
		if (data->meals_num != -1 
			&& check_meals(data->philos, data->meals_num, data->philos_num))
		{
			set_bool(&data->table, &data->dead_flag, true);
			break ;
		}
		int dead_philo = philo_is_dead(data->philos, data->clock, data->philos_num);
		if (dead_philo >= 0)
		{
			set_bool(&data->table, &data->dead_flag, true);
			printf("Dead philo ID is: %d, last eaten meal is: %ld\n", data->philos[dead_philo].philo_id, get_time() - data->clock->start_time);
			print_status(dead_philo, DEAD, data->clock->start_time);
			break ;
		}
	}
}
