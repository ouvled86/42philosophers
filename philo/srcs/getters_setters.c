/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:53:39 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/15 14:42:59 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	get_bool(t_mutex *mtx, bool flag)
{
	bool	ret;

	pthread_mutex_lock(mtx);
	ret = flag;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	set_bool(t_mutex *mtx, bool *flag, bool value)
{
	pthread_mutex_lock(mtx);
	*flag = value;
	pthread_mutex_unlock(mtx);
}

void	set_num(t_mutex *mtx, size_t *des, size_t value)
{
	pthread_mutex_lock(mtx);
	*des = value;
	pthread_mutex_unlock(mtx);
}

size_t	get_num(t_mutex *mtx, size_t *num)
{
	size_t	ret;

	pthread_mutex_unlock(mtx);
	ret = *num;
	pthread_mutex_unlock(mtx);
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
		usleep(us / 4);
}
