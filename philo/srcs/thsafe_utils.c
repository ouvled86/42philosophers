/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thsafe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:53:39 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/10 11:52:32 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	safe_bool(bool *flag, t_operation op, t_mutex *mtx, bool value)
{
	bool	ret;

	ret = false;
	if (op == READ)
	{
		table_mutex(mtx, LOCK);
		ret = *flag;
		table_mutex(mtx, UNLOCK);
	}
	else if (op == WRITE)
	{
		table_mutex(mtx, LOCK);
		*flag = value;
		table_mutex(mtx, UNLOCK);
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
