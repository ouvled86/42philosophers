/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/08 21:51:23 by ouel-bou         ###   ########.fr       */
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

void	create_mutex(t_table *data, int count)
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
			printf("Philo ID: %d, 1st fork address: %p, 2nd fork address: %p\n", i, philos[i].first_fork, philos[i].second_fork);
		}
		else
		{
			philos[i].first_fork = &table->forks[(i + 1) % table->philos_num];
			philos[i].second_fork = &table->forks[i];
			printf("Philo ID: %d, 1st fork address: %p, 2nd fork address: %p\n", i, philos[i].first_fork, philos[i].second_fork);
		}
		i++;
	}
}

void	init_data(t_table **data)
{
	t_table	*table;
	t_philo	*philos;
	int		i;

	table = *data;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_num);
	table->forks = (t_mutex *)malloc(sizeof(t_mutex) * table->philos_num);
	philos = table->philos;
	if (!table->philos || !table->forks)
		err_exit(81, "Malloc failed\n");
	create_mutex(table, table->philos_num);
	assign_forks(table);
}

int	main(int ac, char **av)
{
	t_table	*data;

	data = check_args_input(ac, av);
	init_data(&data);
	for (int i = 0; i < data->philos_num; i++)
		thread_handle(data->philos, JOIN, i);
}
