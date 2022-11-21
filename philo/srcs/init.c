/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:38:59 by nradal            #+#    #+#             */
/*   Updated: 2022/11/21 11:42:23 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.philosophers)
	{
		pthread_mutex_init(&data->philo[i].fork, NULL);
		i++;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.philosophers)
	{
		data->philo[i].data = data;
		data->philo[i].id = i;
		data->philo[i].last_meal = 0;
		data->philo[i].is_alive = 0;
		i++;
	}
}

int	solo_philo(t_data *data)
{
	printf("[%d]		%d is thinking\n", 0, 1);
	usleep(data->arg.time_to_die * 1000);
	printf("[%d]		%d died\n", data->arg.time_to_die, 1);
	return (2);
}

int	init_struct(int argc, char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->arg.time_to_die = ft_atoi(argv[2]);
	data->arg.philosophers = ft_atoi(argv[1]);
	if (data->arg.philosophers == 1)
		return (solo_philo(data));
	data->arg.time_to_eat = ft_atoi(argv[3]);
	data->arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->arg.must_eat = ft_atoi(argv[5]);
	else
		data->arg.must_eat = -1;
	data->thread = ft_calloc(data->arg.philosophers, sizeof(pthread_t));
	data->philo = ft_calloc(data->arg.philosophers, sizeof(t_philo));
	if (!data->thread || !data->philo)
		return (1);
	return (0);
}

int	init_all(int argc, char **argv, t_data *data)
{
	int	i_struct;

	i_struct = init_struct(argc, argv, data);
	if (i_struct == 1)
		return (1);
	else if (i_struct == 2)
		return (2);
	init_mutex(data);
	init_philo(data);
	return (0);
}
