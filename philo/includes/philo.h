/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-bou <ouel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:33:06 by ouel-bou          #+#    #+#             */
/*   Updated: 2024/10/08 18:52:26 by ouel-bou         ###   ########.fr       */
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
	pthread_t	thread;
	int			philo_id;
	int			meals_eaten;
	size_t		last_meal;
	t_mutex		*first_fork;
	t_mutex		*second_fork;
	t_table		*table;
}				t_philo;

typedef struct s_clock
{
	size_t		t_to_die;
	size_t		t_to_eat;
	size_t		t_to_sleep;
}				t_clock;

typedef struct s_table
{
	int			meals_num;
	int			philos_num;
	bool		dead_flag;
	t_philo		*philos;
	t_mutex		*forks;
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

size_t	ft_atol(char *s);
size_t	ft_strlen(char *s);
bool	check_num(char *av);
t_table	*check_args_input(int ac, char **av);
void	err_exit(int status, char *msg);
bool	check_clock(t_clock *c);

void	thread_handle(t_philo *philos, t_calls call, int thread_id);
void	mutex_handle(t_mutex *forks, t_calls call, int fork_id);
void	handle_errno(int status);

void	*func(void *data);


#endif