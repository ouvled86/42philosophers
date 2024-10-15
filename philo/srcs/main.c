/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/15 15:34:46 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	*data;

	data = check_args_input(ac, av);
	init_data(&data);
	for (int i = 0; i < data->philos_num; i++)
		printf("Philo ID is: %d - First fork address: %p - Second fork address: %p - %d\nTABLE ADDRESS: %p\n", data->philos[i].philo_id, data->philos[i].first_fork, data->philos[i].second_fork, data->philos_num, data);
	launch_dinner(data);
}
