/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:53:50 by nradal            #+#    #+#             */
/*   Updated: 2022/11/21 11:08:54 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fs_and_return(t_data *data, int ret)
{
	free_structs(data);
	return (ret);
}

void	free_data(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->thread)
		free(data->thread);
}

void	free_structs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.philosophers)
	{
		pthread_mutex_destroy(&data->philo[i].fork);
		i++;
	}
	free_data(data);
}
