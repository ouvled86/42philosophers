/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:53:39 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/17 13:52:27 by ouel-bou         ###   ########.fr       */
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

void	set_num(t_mutex *mtx, long *des, long value)
{
	pthread_mutex_lock(mtx);
	*des = value;
	pthread_mutex_unlock(mtx);
}

long	get_num(t_mutex *mtx, long *num)
{
	long	ret;

	pthread_mutex_unlock(mtx);
	ret = *num;
	pthread_mutex_unlock(mtx);
	return (ret);
}

long	get_time(void)
{
	struct timeval	tp;
	long			ret;

	if (gettimeofday(&tp, NULL) == -1)
		err_exit(-1, "Gettimeofday failed");
	ret = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (ret);
}
