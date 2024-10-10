/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:15:58 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/10 15:34:47 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	launch_dinner(t_table *data)
{
	create_philos(data, data->philos_num);
	safe_bool(&data->start_flag, WRITE, &data->write, true);
	pthread_create(&data->monitor, NULL, meow, data);
}
