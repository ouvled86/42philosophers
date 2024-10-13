/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/12 19:47:24 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	*data;

	data = check_args_input(ac, av);
	init_data(&data);
	for (int i = 0; i < data->philos_num; i++)
		printf("Philo ID: %d\n", data->philos[i].philo_id);
	launch_dinner(data);
	
}
