/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thsafe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:53:39 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/14 19:55:44 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	safe_bool(bool *flag, t_operation op, t_mutex *mtx, bool value)
{
	bool	ret;

	ret = false;
	if (op == READ)
	{
		pthread_mutex_lock(mtx);
		printf("R-Table mutex locked\n");
		ret = *flag;
		pthread_mutex_unlock(mtx);
		printf("R - Table mutex unlocked, the value is %d\n", *flag);
	}
	else if (op == WRITE)
	{
		pthread_mutex_lock(mtx);
		printf("Table mutex locked\n");
		*flag = value;
		pthread_mutex_unlock(mtx);
		printf("Table mutex unlocked, the value is %d\n", *flag);
	}
	return (ret);
}



size_t	safe_num(size_t *num, t_operation op, t_mutex *mtx, size_t value)
{
	size_t	ret;

	ret = -1;
	if (op == READ)
	{
		table_mutex(mtx, LOCK);
		ret = *num;
		table_mutex(mtx, UNLOCK);
	}
	else if (op == WRITE)
	{
		table_mutex(mtx, LOCK);
		*num = value;
		table_mutex(mtx, UNLOCK);
	}
	return (ret);
}

size_t	get_time(void)
{
	struct timeval	tp;
	size_t			ret;

	if (gettimeofday(&tp, NULL) == -1)
		err_exit(-1, "Gettimeofday failed");
	ret = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (ret);
}

void	print_status(int phid, t_status status, size_t start_time)
{
	size_t	current_time;

	current_time = get_time() - start_time;
	if (status == FORK)
		printf("%ld %d has taken a fork", current_time, phid);
	else if (status == EAT)
		printf("%ld %d is eating", current_time, phid);
	else if (status == SLEEP)
		printf("%ld %d is sleeping", current_time, phid);
	else if (status == THINK)
		printf("%ld %d is thinking", current_time, phid);
	else if (status == DEAD)
		printf("%ld %d died", current_time, phid);
}

void	psleep(size_t us)
{
	size_t	current_time;

	current_time = get_time();
	while (get_time() - current_time < us)
		usleep(us / 5);
}
