/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:56:25 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/15 16:26:54 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_meals(t_philo *philos, int meals_num, int count)
{
	bool	ret;
	int		i;

	ret = true;
	i = 0;
	while (i < count)
	{
		if (philos->meals_eaten < meals_num)
			ret = false;
		i++;
	}
	return (ret);
}

int	philo_is_dead(t_philo *philos, t_clock *clock, int count)
{
	int		ret;
	int		i;

	ret = -1;
	i = 0;
	while (i < count)
	{
		if (philos[i].last_meal != -1)
		{
			if (get_time() - philos[i].last_meal >= clock->t_to_die)
				ret = i + 1;
		}
		else
		{
			if (get_time() - clock->start_time >= clock->t_to_die)
				ret = i + 1;
		}
		i++;
	}
	return (ret);
}

// void	*monitor_routine(void *data)
// {
// 	t_table	*table;
// 	t_clock	*clock;
// 	int		dead_philo;

// 	table = (t_table *)data;
// 	clock = table->clock;
// 	dead_philo = -1;
// 	while (86)
// 	{
// 		if (table->meals_num != -1 
// 			&& check_meals(table->philos, table->meals_num, table->philos_num))
// 		{
// 			safe_bool(&table->finish_flag, WRITE, &table->write, true);
// 			break ;
// 		}
// 		dead_philo = philo_is_dead(table->philos, clock, table->philos_num);
// 		if (dead_philo >= 0)
// 		{
// 			safe_bool(&table->dead_flag, WRITE, &table->write, true);
// 			print_status(dead_philo, DEAD, clock->start_time);
// 			break ;
// 		}
// 	}
// 	return (NULL);
// }

void	philo_eat(t_philo *philo, t_clock *clock)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo->philo_id, FORK, clock->start_time);
	pthread_mutex_lock(philo->second_fork);
	print_status(philo->philo_id, FORK, clock->start_time);
	print_status(philo->philo_id, EAT, clock->start_time);
	philo->meals_eaten++;
	philo->last_meal = get_time();
	psleep(clock->t_to_eat * 1000);
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
	{
		printf("Philo ID %d is currently sleeping for %ld ms to avoid deadlock\n", philo->philo_id, table->clock->t_to_eat / 2);
		usleep(30 * 1e3);
	}
	while (!get_bool(&table->table, table->finish_flag))
	{
		if (table->meals_num != -1 && table->meals_num == philo->meals_eaten)
			break ;
		philo_eat(philo, table->clock);
		philo_sleep(philo, table->clock);
		philo_think(philo, table->clock);
	}
	return (NULL);
}

	// printf("Dead flag: ~ finish flag: %d\n", philo->table->finish_flag);
	// printf("THS - CURRENT TIME: %ld ~ start flag: %d\n", get_time(), philo->table->start_flag);
	// printf("Simulation started, TH ID: %p, philo ID: %d table address: %p\n", &philo->thread, philo->philo_id, table);
	// printf("Simulation started\n");