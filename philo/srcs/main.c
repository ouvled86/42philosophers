/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/06 01:14:10 by ouel-bou         ###   ########.fr       */
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
	{
		mutex_handle(data->forks, INIT, i);
		i++;
	}
}

void	init_data(t_table **data)
{
	t_table	*table;

	table = *data;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_num);
	table->forks = (t_mutex *)malloc(sizeof(t_mutex) * table->philos_num);
	if (!table->philos || !table->forks)
		err_exit(81, "Malloc failed\n");
	create_philos(table, table->philos_num);
	create_mutex(table, table->philos_num);
}

int	main(int ac, char **av)
{
	t_table	*data;

	data = check_args_input(ac, av);
	init_data(&data);
	for (int i = 0; i < data->philos_num; i++)
		thread_handle(data->philos, JOIN, i);
}
