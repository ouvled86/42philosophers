/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:56:25 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/16 11:57:19 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo, t_clock *clock)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo->philo_id, FORK, clock->start_time);
	pthread_mutex_lock(philo->second_fork);
	print_status(philo->philo_id, FORK, clock->start_time);
	print_status(philo->philo_id, EAT, clock->start_time);
	philo->last_meal = get_time();
	psleep(clock->t_to_eat * 1000);
	philo->meals_eaten++;
	if (philo->table->meals_num != -1 
		&& philo->table->meals_num == philo->meals_eaten)
		philo->full = true;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_sleep(t_philo *philo, t_clock *clock)
{
	print_status(philo->philo_id, SLEEP, clock->start_time);
	psleep(clock->t_to_sleep * 1000);
}

void	philo_think(t_philo *philo, t_clock *clock)
{
	print_status(philo->philo_id, THINK, clock->start_time);
}

void	wait_start(t_table *table)
{
	while (!get_bool(&table->table, table->start_flag))
		usleep(1);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_start(philo->table);
	if (philo->philo_id % 2 == 0)
		usleep(30 * 1e3);
	while (!get_bool(&table->table, table->finish_flag))
	{
		philo_eat(philo, table->clock);
		philo_sleep(philo, table->clock);
		philo_think(philo, table->clock);
	}
	return (NULL);
}
