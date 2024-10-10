/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:54:21 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/10 11:54:59 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_philos(t_table *data, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		thread_handle(data->philos, CREATE, i);
		data->philos[i].philo_id = i;
		data->philos[i].table = data;
		i++;
	}
}

void	create_forks(t_table *data, int count)
{
	int		i;

	i = 0;
	while (i < count)
		mutex_handle(data->forks, INIT, i++);
}

void	assign_forks(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	i = 0;
	while (i < table->philos_num)
	{
		if (philos[i].philo_id % 2 == 0)
		{
			philos[i].first_fork = &table->forks[i];
			philos[i].second_fork = &table->forks[(i + 1) % table->philos_num];
		}
		else
		{
			philos[i].first_fork = &table->forks[(i + 1) % table->philos_num];
			philos[i].second_fork = &table->forks[i];
		}
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
	assign_forks(table);
	table->start_flag = false;
	table->dead_flag = false;
	table_mutex(&table->read, INIT);
	table_mutex(&table->write, INIT);
}
