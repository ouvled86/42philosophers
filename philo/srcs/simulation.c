/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/15 15:46:52 by ouel-bou         ###   ########.fr       */
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
	while(1);
}
