/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:37:12 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 17:45:09 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_begin_simulation(pthread_t **philo,
			struct s_data *data, struct s_phdata **phdata)
{
	int	i;

	i = 0;
	data->starttime = ft_time_us();
	while (i < data->num_philo)
	{
		phdata[i]->last_eaten = phdata[i]->data->starttime;
		pthread_create(philo[i], NULL, ft_philo_thread, (void *)phdata[i]);
		i++;
	}
	return ;
}

void	ft_check_death(struct s_data *data, struct s_phdata **phdata)
{
	int	i;

	i = 0;
	while (ft_still_eating_get(data))
	{
		ft_is_this_philo_dead(phdata[i], ft_time_us());
		i = (i + 1) % data->num_philo;
		usleep(1000 / data->num_philo);
	}
	return ;
}

void	ft_end_simulation(pthread_t **philo, struct s_data *data)
{
	int	join_thread;

	usleep (data->time_to_die * 1100);
	join_thread = 0;
	while (join_thread < data->num_philo)
	{
		pthread_join(*philo[join_thread], NULL);
		free(philo[join_thread]);
		join_thread++;
	}
	return ;
}
