/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:50:02 by nradal            #+#    #+#             */
/*   Updated: 2022/11/21 11:31:08 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <sys/time.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define EAT	0
# define SLEEP	1
# define THINK	2
# define FORK	3
# define DEAD	4

# define LOCK	1
# define UNLOCK 0

# define STOPPED 1
# define RUNNING 0

typedef struct s_data	t_data;

typedef struct s_arg
{
	int	philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}				t_arg;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				last_meal;
	int				meal_counter;
	pthread_mutex_t	fork;
	int				is_alive;
}				t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	pthread_t		*thread;
	pthread_t		monitoring;
	t_arg			arg;
	int				thread_state;
	long			starting_time;
}				t_data;

// PARSE_ARGS.C
int			parse_args(int argc, char **argv);
// UTILS.C
int			ft_atoi(char *str);
long		get_time(void);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
// INIT.C
int			init_all(int agrc, char **argv, t_data *data);
// ACTIONS.C
int			print_action(t_philo *philo, int action);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
// MEMORY.C
void		free_structs(t_data *data);
void		free_data(t_data *data);
int			fs_and_return(t_data *data, int ret);
// THREADS.C
void		*routine(void *param);
int			monitoring_loop(t_data *data, int meal_goal);
void		*monitoring(void *param);
int			threads(t_data *data, pthread_t *thread, t_philo *philo);

#endif