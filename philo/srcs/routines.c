/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:56:25 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/19 20:33:46 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_eat(t_philo *philo, t_clock *clock)
{
	if (get_bool(&philo->table->table, &philo->table->dead_flag)
		|| get_bool(&philo->table->table, &philo->table->finish_flag)
		|| get_bool(&philo->table->table, &philo->full))
		return (1);
	pthread_mutex_lock(philo->first_fork);
	print_status(philo->philo_id, FORK, clock->start_time, philo->table);
	pthread_mutex_lock(philo->second_fork);
	set_num(&philo->table->time, &philo->last_meal, get_time());
	set_num(&philo->table->meals, &philo->meals_eaten, 
		get_num(&philo->table->meals, &philo->meals_eaten) + 1);
	if (philo->table->meals_num != -1 
		&& philo->table->meals_num == philo->meals_eaten)
		set_bool(&philo->table->meals, &philo->full, true);
	print_status(philo->philo_id, FORK, clock->start_time, philo->table);
	print_status(philo->philo_id, EAT, clock->start_time, philo->table);
	psleep(clock->t_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return (0);
}

static int	philo_sleep(t_philo *philo, t_clock *clock)
{
	if (get_bool(&philo->table->table, &philo->table->dead_flag)
		|| get_bool(&philo->table->table, &philo->table->finish_flag))
		return (1);
	print_status(philo->philo_id, SLEEP, clock->start_time, philo->table);
	psleep(clock->t_to_sleep * 1000);
	return (0);
}

static int	philo_think(t_philo *philo, t_clock *clock)
{
	if (get_bool(&philo->table->table, &philo->table->dead_flag)
		|| get_bool(&philo->table->table, &philo->table->finish_flag))
		return (1);
	print_status(philo->philo_id, THINK, clock->start_time, philo->table);
	return (0);
}

static void	wait_start(t_table *table)
{
	while (!get_bool(&table->table, &table->start_flag))
		;
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
	set_num(&table->time, &philo->last_meal, get_num(&table->table, 
			&table->clock->start_time));
	while (!get_bool(&table->table, &table->dead_flag)
		&& !get_bool(&table->table, &table->finish_flag))
	{
		if (table->meals_num == 0)
			break ;
		if (philo_eat(philo, table->clock))
			break ;
		if (philo_sleep(philo, table->clock))
			break ;
		if (philo_think(philo, table->clock))
			break ;
	}
	return (NULL);
}
