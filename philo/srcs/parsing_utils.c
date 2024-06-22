/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:51:27 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/06/22 20:59:27 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char *s)
{
	size_t	r;

	r = 0;
	while (s[r])
		r++;
	return (r);
}

bool	check_num(char *av)
{
	int		i;
	bool	flag;

	i = 0;
	flag = true;
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == 32)
		i++;
	if (!(av[i] >= '0' && av[i] < '9') || av[i] != '+')
		flag = false;
	return (flag);
}

size_t	ft_atol(char *s)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = ret * 10 + (s[i] - '0');
		i++;
	}
	return (ret);
}

bool	check_clock(t_clock *c)
{
	bool	ret;

	ret = true;
	if (c->t_to_die > INT_MAX || c->t_to_eat > INT_MAX 
		|| c->t_to_sleep > INT_MAX)
		ret = false;
	return (ret);
}
