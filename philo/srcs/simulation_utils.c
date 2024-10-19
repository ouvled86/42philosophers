/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:39:26 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/19 20:05:34 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(int phid, t_status status, long start_time, t_table *data)
{
	long	current_time;

	pthread_mutex_lock(&data->status);
	current_time = get_time() - start_time;
	if (status == FORK && !get_bool(&data->table, &data->dead_flag)
		&& !get_bool(&data->table, &data->finish_flag))
		printf("%ld %d has taken a fork\n", current_time, phid);
	else if (status == EAT && !get_bool(&data->table, &data->dead_flag)
		&& !get_bool(&data->table, &data->finish_flag))
		printf("%ld %d is eating\n", current_time, phid);
	else if (status == SLEEP && !get_bool(&data->table, &data->dead_flag)
		&& !get_bool(&data->table, &data->finish_flag))
		printf("%ld %d is sleeping\n", current_time, phid);
	else if (status == THINK && !get_bool(&data->table, &data->dead_flag)
		&& !get_bool(&data->table, &data->finish_flag))
		printf("%ld %d is thinking\n", current_time, phid);
	else if (status == DEAD)
	{
		printf("%ld %d died\n", current_time, phid);
		psleep(1000);
	}
	pthread_mutex_unlock(&data->status);
}

void	psleep(long us)
{
	long	current_time;

	current_time = get_time();
	while (get_time() - current_time < us / 1e3)
		usleep(100);
}

void	clean_data(t_table *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->status);
	pthread_mutex_destroy(&data->table);
	free(data->philos);
	free(data->forks);
	free(data->clock);
	free(data);
}
