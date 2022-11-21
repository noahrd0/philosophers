/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:31:13 by nradal            #+#    #+#             */
/*   Updated: 2022/11/21 11:31:15 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if ((philo->id + 1) % 2 == 0)
	{
		print_action(philo, THINK);
		usleep(philo->data->arg.time_to_eat * 1000);
	}
	while (1)
	{
		if (eating(philo) == STOPPED)
			break ;
		if (sleeping(philo) == STOPPED)
			break ;
		if (print_action(philo, THINK) == STOPPED)
			break ;
	}
	return ((void *)1);
}

int	monitoring_loop(t_data *data, int meal_goal)
{
	int	i;

	i = 0;
	while (i < data->arg.philosophers)
	{
		if (get_time() - data->starting_time
			> data->philo[i].last_meal + data->arg.time_to_die)
		{
			print_action(&data->philo[i], DEAD);
			data->thread_state = STOPPED;
			return (-1);
		}
		if (data->philo[i].meal_counter == data->arg.must_eat)
		{
			meal_goal++;
			data->philo[i].meal_counter++;
			if (meal_goal == data->arg.philosophers)
			{
				data->thread_state = STOPPED;
				return (-1);
			}
		}
		i++;
	}
	return (meal_goal);
}

void	*monitoring(void *param)
{
	t_data	*data;
	int		meal_goal;

	data = (t_data *)param;
	meal_goal = 0;
	while (data->thread_state == RUNNING)
	{
		meal_goal = monitoring_loop(data, meal_goal);
		if (meal_goal == -1)
			break ;
	}
	return (NULL);
}

int	threads(t_data *data, pthread_t *thread, t_philo *philo)
{
	int	i;

	i = 0;
	data->starting_time = get_time();
	data->thread_state = RUNNING;
	while (i < data->arg.philosophers)
	{
		if (pthread_create(&thread[i], NULL, &routine, &philo[i]) != 0)
			return (fs_and_return(data, 1));
		i++;
	}
	if (pthread_create(&data->monitoring, NULL, &monitoring, data) != 0)
		return (fs_and_return(data, 1));
	i = 0;
	while (i < data->arg.philosophers)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (fs_and_return(data, 1));
		i++;
	}
	return (0);
}
