/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:14:03 by nradal            #+#    #+#             */
/*   Updated: 2022/11/18 23:34:42 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	print_action(t_philo *philo, int action)
{
	if (philo->data->thread_state == STOPPED)
		return (STOPPED);
	if (action == EAT)
		printf("[%lu]		%d is eating\n",
			get_time() - philo->data->starting_time, philo->id + 1);
	else if (action == SLEEP)
		printf("[%lu]		%d is sleeping\n",
			get_time() - philo->data->starting_time, philo->id + 1);
	else if (action == THINK)
		printf("[%lu]		%d is thinking\n",
			get_time() - philo->data->starting_time, philo->id + 1);
	else if (action == FORK)
		printf("[%lu]		%d has taken a fork\n",
			get_time() - philo->data->starting_time, philo->id + 1);
	else if (action == DEAD)
	{
		printf("[%lu]		%d died\n",
			get_time() - philo->data->starting_time, philo->id + 1);
		return (STOPPED);
	}
	return (RUNNING);
}

int	taking_fork(t_philo *philo, int action)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(&philo->fork);
		if (print_action(philo, FORK) == STOPPED)
			return (STOPPED);
		if (philo->id == 0)
			pthread_mutex_lock
				(&philo->data->philo[philo->data->arg.philosophers - 1].fork);
		else
			pthread_mutex_lock(&philo->data->philo[philo->id - 1].fork);
		if (print_action(philo, FORK) == STOPPED)
			return (STOPPED);
	}
	else if (action == UNLOCK)
	{
		pthread_mutex_unlock(&philo->fork);
		if (philo->id == 0)
			pthread_mutex_unlock
				(&philo->data->philo[philo->data->arg.philosophers - 1].fork);
		else
			pthread_mutex_unlock(&philo->data->philo[philo->id - 1].fork);
	}
	return (RUNNING);
}

int	eating(t_philo *philo)
{
	taking_fork(philo, LOCK);
	if (print_action(philo, EAT) == STOPPED)
		return (STOPPED);
	philo->last_meal = get_time() - philo->data->starting_time;
	usleep(philo->data->arg.time_to_eat * 1000);
	taking_fork(philo, UNLOCK);
	philo->meal_counter++;
	return (RUNNING);
}

int	sleeping(t_philo *philo)
{
	if (print_action(philo, SLEEP) == STOPPED)
		return (STOPPED);
	usleep(philo->data->arg.time_to_sleep * 1000);
	return (RUNNING);
}
