/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:51:27 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/06/14 22:51:42 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
