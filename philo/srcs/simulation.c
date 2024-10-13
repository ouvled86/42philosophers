/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/12 19:57:03 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	launch_dinner(t_table *data)
{
	// create_philos(data, data->philos_num);
	for (int i = 0; i < data->philos_num; i++)
		philo_handle(data->philos, CREATE, i);
	// for (int i = 0; i < data->philos_num; i++)
	// 	printf("Philo ID: %d - Thread ID: %ld\n", data->philos[i].philo_id, data->philos[i].thread);
	safe_bool(&data->start_flag, WRITE, &data->write, true);
	safe_num(&data->clock->start_time, WRITE, &data->write, get_time());
	// while (!data->finish_flag && !data->dead_flag)
	// 	;
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	for (int i = 0; i < data->philos_num; i++)
		philo_handle(data->philos, JOIN, i);
	// for (int i = 0; i < data->philos_num; i++)
	// 	fork_handle(&data->forks[i], DESTROY);
	// pthread_join(data->monitor, NULL);
	// pthread_mutex_destroy(&data->read);
	// pthread_mutex_destroy(&data->write);
}
