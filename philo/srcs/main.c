/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/06/14 19:50:17 by ouel-bou         ###   ########.fr       */
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

bool	check_input(char **av)
{
	bool	flag;
	int		i;

	i = 2;
	flag = true;
	if (ft_strlen(av[1]) > 3)
		flag = false;
	if (ft_strlen(av[2]) > 10 || ft_strlen(av[3]) > 10 
		|| ft_strlen(av[4]) > 10)
		flag = false;
	while (i < 5)
	{
		flag = check_num(av[i]);
		i++;
	}
	return (flag);
}

bool	args_count(int ac)
{
	if (ac == 5 || ac == 6)
		return (true);
	return (false);
}

bool	parse_input(char **av, t_clock *clock)
{
	
}

int	check_args_input(int ac, char **av, t_table *data)
{
	t_clock	*clock;
	t_table	*table;

	clock = NULL;
	if (args_count(ac) != true)
		exit (10);
	if (check_input(av) != true)
		exit (11);
	if (parse_input(av, clock) != true)
		exit (12);
	table = (t_table *)malloc(sizeof(t_table));
	table->clock = clock;
	data = table;
}

int	main(int ac, char **av)
{
	t_table	*data;
	check_args_input(ac, av, data);
}
