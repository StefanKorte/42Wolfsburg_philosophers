/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:44:27 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 20:02:00 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_update_last_eaten(struct s_phdata *phdata, unsigned long start)
{
	pthread_mutex_lock(phdata->last_eaten_mutex);
	phdata->last_eaten = start;
	pthread_mutex_unlock(phdata->last_eaten_mutex);
}

int	ft_still_eating_get(struct s_data *data)
{
	int	philos_still_eating;

	pthread_mutex_lock(data->philos_still_eating_mutex);
	philos_still_eating = data->philos_still_eating;
	pthread_mutex_unlock(data->philos_still_eating_mutex);
	return (philos_still_eating);
}

int	ft_still_eating_minus(struct s_data *data)
{
	int	philos_still_eating;

	pthread_mutex_lock(data->philos_still_eating_mutex);
	if (data->philos_still_eating)
		data->philos_still_eating--;
	philos_still_eating = data->philos_still_eating;
	pthread_mutex_unlock(data->philos_still_eating_mutex);
	return (philos_still_eating);
}

int	ft_died(struct s_data *data, unsigned long time, char *str)
{
	pthread_mutex_lock(data->philos_still_eating_mutex);
	if (data->philos_still_eating)
		ft_write_no_test(time, str, data);
	data->philos_still_eating = 0;
	pthread_mutex_unlock(data->philos_still_eating_mutex);
	return (0);
}

int	ft_is_this_philo_dead(struct s_phdata *phdata, unsigned long time)
{
	pthread_mutex_lock(phdata->last_eaten_mutex);
	if (phdata->last_eaten + phdata->data->time_to_die * 1000 < time)
		ft_died(phdata->data, time, phdata->str_died);
	pthread_mutex_unlock(phdata->last_eaten_mutex);
	return (0);
}
