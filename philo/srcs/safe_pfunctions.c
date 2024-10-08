/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:39:26 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/08 19:59:32 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// bool	check_meals(t_philo *philos, int meals_num, int count)
// {
// 	bool	ret;
// 	int		i;

// 	ret = true;
// 	i = 0;
// 	while (i < count)
// 	{
// 		if (philos->meals_eaten < meals_num)
// 			ret = false;
// 		i++;
// 	}
// 	return (ret);
// }

// void	*monitor_routine(void *data)
// {
// 	t_table	*table;

// 	table = (t_table *)data;
// 	while (86)
// 	{
// 		if (table->dead_flag)
// 			break ;
// 		if (table->meals_num != -1 
// 			&& check_meals(table->philos, table->meals_num, table->philos_num))
// 			break ;
// 	}
// 	// clean up
// }

// void	*philo_routine(void *data)
// {
// 	t_philo	*philo;
// 	t_table	*table;
// 	t_mutex	*mutex;

// 	philo = (t_philo *)data;
// 	table = philo->table;
// 	mutex_handle(philo->first_fork, LOCK);
// 	// print started eating and save last meal!
// 	mutex_handle(philo->second_fork, LOCK);
// 	// create a precise sleeping function to sleep the eating thread
// }

void	*func(void *data)
{
	sleep(20);
	return NULL;
}

void	thread_handle(t_philo *philos, t_calls call, int thread_id)
{
	t_philo	philo;
	int		status;

	philo = philos[thread_id];
	status = 0;
	if (call == CREATE)
		status = pthread_create(&philo.thread, NULL, func, NULL);
	else if (call == JOIN)
		status = pthread_join(philo.thread, NULL);
	handle_errno(status);
}

void	mutex_handle(t_mutex *forks, t_calls call, int fork_id)
{
	int	status;

	status = 0;
	if (call == INIT)
		status = pthread_mutex_init(&forks[fork_id], NULL);
	else if (call == LOCK)
		status = pthread_mutex_lock(&forks[fork_id]);
	else if (call == UNLOCK)
		status = pthread_mutex_lock(&forks[fork_id]);
	else if (call == DESTROY)
		status = pthread_mutex_destroy(&forks[fork_id]);
	handle_errno(status);
}

void	handle_errno(int status)
{
	if (!status)
		return ;
	else if (status == EDEADLK)
		err_exit(status, "Deadlock detected\n");
	else if (status == EAGAIN)
		err_exit(status, "Maximum number of threads is exceeded\n");
	else if (status == EPERM)
		err_exit(status, "Insufficient permissions\n");
	else if (status == EINVAL)
		err_exit(status, "Thread isn't joinable\n");
	else if (status == ENOMEM)
		err_exit(status, "Insufficient memory\n");
	else if (status == EBUSY)
		err_exit(status, "Mutex already initialized\n");
}
