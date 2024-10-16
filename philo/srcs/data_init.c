/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:21 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/16 13:36:50 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_philos(t_table *data, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].table = data;
		data->philos[i].last_meal = -1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].full = false;
		i++;
	}
}

void	create_forks(t_table *data, int count)
{
	int		i;

	i = 0;
	while (i < count)
		fork_handle(&data->forks[i++], INIT);
}

void	assign_forks(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	i = 0;
	while (i < table->philos_num)
	{
		philos[i].first_fork = &table->forks[i];
		philos[i].second_fork = &table->forks[(i + 1) % table->philos_num];
		i++;
	}
}

void	table_mutex(t_mutex *mtx, t_calls call)
{
	int	status;

	status = 0;
	if (call == INIT)
		status = pthread_mutex_init(mtx, NULL);
	else if (call == LOCK)
		status = pthread_mutex_lock(mtx);
	else if (call == UNLOCK)
		status = pthread_mutex_lock(mtx);
	else if (call == DESTROY)
		status = pthread_mutex_destroy(mtx);
	handle_errno(status);
}

void	init_data(t_table **data)
{
	t_table	*table;

	table = *data;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_num);
	table->forks = (t_mutex *)malloc(sizeof(t_mutex) * table->philos_num);
	if (!table->philos || !table->forks)
		err_exit(81, "Malloc failed\n");
	create_forks(table, table->philos_num);
	create_philos(table, table->philos_num);
	assign_forks(table);
	table->start_flag = false;
	table->dead_flag = false;
	table->finish_flag = false;
	pthread_mutex_init(&table->status, NULL);
	table_mutex(&table->table, INIT);
}
