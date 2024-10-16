/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:39:26 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/16 12:01:08 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_handle(t_philo *philos, t_calls call, int thread_id)
{
	t_philo	philo;
	int		status;

	philo = philos[thread_id];
	status = 0;
	if (call == CREATE)
		status = pthread_create(&philo.thread, NULL, philo_routine,
				&philos[thread_id]);
	else if (call == JOIN)
		status = pthread_join(philo.thread, NULL);
	handle_errno(status);
}

void	fork_handle(t_mutex *fork, t_calls call)
{
	int	status;

	status = 0;
	if (call == INIT)
		status = pthread_mutex_init(fork, NULL);
	else if (call == LOCK)
		status = pthread_mutex_lock(fork);
	else if (call == UNLOCK)
		status = pthread_mutex_lock(fork);
	else if (call == DESTROY)
		status = pthread_mutex_destroy(fork);
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

void	print_status(int phid, t_status status, size_t start_time)
{
	size_t	current_time;

	current_time = get_time() - start_time;
	if (status == FORK)
		printf("%ld %d has taken a fork\n", current_time, phid);
	else if (status == EAT)
		printf("%ld %d is eating\n", current_time, phid);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", current_time, phid);
	else if (status == THINK)
		printf("%ld %d is thinking\n", current_time, phid);
	else if (status == DEAD)
		printf("%ld %d died\n", current_time, phid);
}

void	psleep(size_t us)
{
	size_t	current_time;

	current_time = get_time();
	while (get_time() - current_time < us / 1e3)
		usleep(us / 5);
}
