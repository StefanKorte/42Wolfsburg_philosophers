/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:26:49 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 17:40:38 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(pthread_t **phi, struct s_data *data, struct s_phdata **phdata)
{
	int	i;

	free(phi);
	i = 0;
	while (i < data->num_philo)
	{
		free(phdata[i]->str_taken);
		free(phdata[i]->str_eating);
		free(phdata[i]->str_sleeping);
		free(phdata[i]->str_thinking);
		free(phdata[i]->str_died);
		pthread_mutex_destroy(&data->fork_mutex[i]);
		pthread_mutex_destroy(phdata[i]->last_eaten_mutex);
		free(phdata[i]->last_eaten_mutex);
		free(phdata[i]);
		i++;
	}
	free(phdata);
	free(data->fork_mutex);
	pthread_mutex_destroy(data->philos_still_eating_mutex);
	free(data->philos_still_eating_mutex);
	free(data);
	return ;
}
