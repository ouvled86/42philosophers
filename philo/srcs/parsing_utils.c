/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:51:27 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/17 14:14:37 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_strlen(char *s)
{
	long	r;

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
	if (av[i] == '+')
		i++;
	while (av[i])
	{
		if (!(av[i] >= '0' && av[i] < '9'))
			flag = false;
		i++;
	}
	return (flag);
}

long	ft_atol(char *s)
{
	int		i;
	long	ret;

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
	if (c->t_to_die < 60 || c->t_to_eat < 60 
		|| c->t_to_sleep < 60)
		ret = false;
	return (ret);
}

void	err_exit(int status, char *msg)
{
	printf("%s\n", msg);
	exit (status);
}
