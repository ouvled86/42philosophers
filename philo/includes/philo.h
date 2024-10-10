/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:33:06 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/10 15:31:28 by ouel-bou         ###   ########.fr       */
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
	bool		start_flag;
	size_t		meals_num;
	pthread_t	monitor;
	t_philo		*philos;
	t_mutex		*forks;
	t_mutex		read;
	t_mutex		write;
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

typedef enum e_operation
{
	READ,
	WRITE,
}	t_operation;

size_t	ft_strlen(char *s);
bool	check_num(char *av);
size_t	ft_atol(char *s);
bool	check_clock(t_clock *c);
t_table	*check_args_input(int ac, char **av);
void	err_exit(int status, char *msg);

void	philo_handle(t_philo *philos, t_calls call, int thread_id);
void	fork_handle(t_mutex *forks, t_calls call, int fork_id);
void	handle_errno(int status);

void	create_philos(t_table *data, int count);
void	create_forks(t_table *data, int count);
void	assign_forks(t_table *table);
void	table_mutex(t_mutex *mtx, t_calls call);
void	init_data(t_table **data);

bool	safe_bool(bool *flag, t_operation op, t_mutex *mtx, bool value);
size_t	safe_num(size_t *num, t_operation op, t_mutex *mtx, size_t value);

void	launch_dinner(t_table *data);

void	*func(void *data);

#endif