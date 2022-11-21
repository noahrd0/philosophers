/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradal <nradal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:39:03 by nradal            #+#    #+#             */
/*   Updated: 2022/11/21 11:31:21 by nradal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		init_all_int;

	if (parse_args(argc, argv) == 1)
	{
		printf("Wrong arguments\n");
		return (1);
	}
	init_all_int = init_all(argc, argv, &data);
	if (init_all_int == 1)
	{
		free_data(&data);
		printf("Something went wrong in init\n");
		return (1);
	}
	else if (init_all_int == 2)
		return (0);
	if (threads(&data, data.thread, data.philo) == 1)
	{
		printf("An error occured while launching threads\n");
		return (1);
	}
	free_structs(&data);
	return (0);
}
