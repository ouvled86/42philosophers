/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:39:52 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/06/14 21:12:00 by ouel-bou         ###   ########.fr       */
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
	if (c->t_to_die > INT_MAX || c->t_to_eat > INT_MAX 
		|| c->t_to_sleep > INT_MAX)
		return (false);
	return (true);
}

bool	parse_input(char **av, t_clock *clock)
{
	t_clock	*c;
	bool	flag;

	c = (t_clock *)malloc(sizeof(t_clock));
	if (!c)
		err_exit (40, "Error from malloc()");
	c->t_to_die = ft_atol(av[2]);
	c->t_to_eat = ft_atol(av[3]);
	c->t_to_sleep = ft_atol(av[4]);
	flag = check_clock(c);
	clock = c;
	return (flag);
}

void	check_args_input(int ac, char **av, t_table *data)
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
	table->philos_num = ft_atol(av[1]);
	if (table->philos_num > 200)
		err_exit (50, "Too many philos, max is 200");
	if (!av[5])
		table->meals_num = -1;
	else
		table->meals_num = ft_atol(av[5]);
	table->dead_flag = false;
	data = table;
}

int	main(int ac, char **av)
{
	t_table	*data;

	check_args_input(ac, av, data);
	printf("TTD: %d TTE: %d TTS: %d\n", data->clock->t_to_die, data->clock->t_to_eat, data->clock->t_to_sleep);
}
  