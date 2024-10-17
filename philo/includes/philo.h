/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:33:06 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/17 12:55:19 by ouel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			philo_id;
	bool		full;
	size_t		meals_eaten;
	size_t		last_meal;
	t_mutex		*first_fork;
	t_mutex		*second_fork;
	t_table		*table;
	pthread_t	thread;
}				t_philo;

typedef struct s_clock
{
	size_t		t_to_die;
	size_t		t_to_eat;
	size_t		t_to_sleep;
	size_t		start_time;
}				t_clock;

typedef struct s_table
{
	int			philos_num;
	bool		dead_flag;
	bool		finish_flag;
	bool		start_flag;
	size_t		meals_num;
	t_philo		*philos;
	t_mutex		*forks;
	t_mutex		table;
	t_mutex		status;
	t_clock		*clock;
}				t_table;

typedef enum e_calls
{
	CREATE,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_calls;

typedef enum e_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_status;

size_t	ft_strlen(char *s);
bool	check_num(char *av);
size_t	ft_atol(char *s);
bool	check_clock(t_clock *c);
t_table	*check_args_input(int ac, char **av);
void	err_exit(int status, char *msg);

void	create_philos(t_table *data, int count);
void	create_forks(t_table *data, int count);
void	assign_forks(t_table *table);
void	init_data(t_table **data);

bool	get_bool(t_mutex *mtx, bool flag);
void	set_bool(t_mutex *mtx, bool *flag, bool value);
size_t	get_num(t_mutex *mtx, size_t *num);
void	set_num(t_mutex *mtx, size_t *des, size_t value);
size_t	get_time(void);
void	print_status(int phid, t_status status, size_t start_time, 
			t_mutex *mtx);
void	psleep(size_t us);

void	*philo_routine(void *data);

void	launch_dinner(t_table *data);
void	monitor_dinner(t_table *data);
void	clean_data(t_table *data);

#endif