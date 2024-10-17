/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:56:25 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/17 14:06:28 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_eat(t_philo *philo, t_clock *clock)
{
	pthread_mutex_lock(philo->first_fork);
	if (get_bool(&philo->table->table, philo->table->dead_flag)
		|| get_bool(&philo->table->table, philo->table->finish_flag)
		|| get_bool(&philo->table->table, philo->full))
		exit (0);
	print_status(philo->philo_id, FORK, clock->start_time, 
		&philo->table->status);
	pthread_mutex_lock(philo->second_fork);
	philo->last_meal = get_time();
	print_status(philo->philo_id, FORK, clock->start_time, 
		&philo->table->status);
	print_status(philo->philo_id, EAT, clock->start_time, 
		&philo->table->status);
	psleep(clock->t_to_eat * 1000);
	philo->meals_eaten++;
	if (philo->table->meals_num != -1 
		&& philo->table->meals_num == philo->meals_eaten)
		philo->full = true;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static void	philo_sleep(t_philo *philo, t_clock *clock)
{
	if (get_bool(&philo->table->table, philo->table->dead_flag)
		|| get_bool(&philo->table->table, philo->table->finish_flag))
		exit (0);
	print_status(philo->philo_id, SLEEP, clock->start_time, 
		&philo->table->status);
	psleep(clock->t_to_sleep * 1000);
}

static void	philo_think(t_philo *philo, t_clock *clock)
{
	if (get_bool(&philo->table->table, philo->table->dead_flag)
		|| get_bool(&philo->table->table, philo->table->finish_flag))
		exit (0);
	print_status(philo->philo_id, THINK, clock->start_time, 
		&philo->table->status);
}

static void	wait_start(t_table *table)
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
	set_num(&table->table, &philo->last_meal, table->clock->start_time);
	while (!get_bool(&table->table, table->dead_flag)
		&& !get_bool(&table->table, table->finish_flag))
	{
		if (table->meals_num == 0)
			break ;
		philo_eat(philo, table->clock);
		philo_sleep(philo, table->clock);
		philo_think(philo, table->clock);
	}
	return (NULL);
}
