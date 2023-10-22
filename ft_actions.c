/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:21:30 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 20:19:10 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** An action first logs the start time, then writes its message,
** and only afterwards calculates the remaining sleep that is necessary.
**
** This prevents delays from the write to terminal.
*/

void	ft_sleeping(struct s_phdata *phdata)
{
	unsigned long	start;
	int				wait;

	start = ft_time_us();
	ft_write(start, phdata->str_sleeping, phdata->data);
	wait = phdata->data->time_to_sleep * 1000 + (int)start - (int)ft_time_us();
	if (wait > 0)
		usleep(wait);
	return ;
}

/*
** Every second philosopher thinks a few microseconds.
** In case that there is an uneven number of philosophers,
** every second philosopher thinks half the time
** that their neighbours need to eat. 
*/

void	ft_thinking(struct s_phdata *phdata)
{
	unsigned long	start;

	start = ft_time_us();
	ft_write(start, phdata->str_thinking, phdata->data);
	if (phdata->philo_num % 2 && phdata->data->num_philo % 2)
		usleep(phdata->data->time_to_eat * 500);
	else if (phdata->philo_num % 2
		&& phdata->data->starttime == phdata->last_eaten)
		usleep(100 * phdata->data->num_philo);
	return ;
}

/*
** Eating process.
** Writes its start time to phdata->last_eaten for the calling philosopher.
** Decreases the meals_num togo counter by one for the calling philosopher.
*/

void	ft_eating(struct s_phdata *phdata)
{
	unsigned long	start;
	int				wait;

	start = ft_time_us();
	ft_is_this_philo_dead(phdata, start);
	ft_update_last_eaten(phdata, start);
	if (!ft_still_eating_get(phdata->data))
		NULL;
	else
	{
//		ft_write(start, phdata->str_eating, phdata->data);
		phdata->meal_num--;
//		if (!phdata->meal_num)
//			ft_still_eating_minus(phdata->data);
		{
			pthread_mutex_lock(phdata->data->philos_still_eating_mutex);
			if (phdata->data->philos_still_eating)
			{
				ft_write_no_test(start, phdata->str_eating, phdata->data);
				if (!phdata->meal_num)
					phdata->data->philos_still_eating--;
			}
			pthread_mutex_unlock(phdata->data->philos_still_eating_mutex);
		}
	}
	wait = phdata->data->time_to_eat * 1000 + (int)start - (int)ft_time_us();
	if (wait > 0)
		usleep(wait);
	return ;
}

/*
** If only one philosopher is present, only one fork will be picked.
** The philosopher will wait to die.
*/

void	ft_grab_forks(struct s_phdata *phdata)
{
	pthread_mutex_lock(&phdata->data->fork_mutex[phdata->fork_1]);
	ft_write(ft_time_us(), phdata->str_taken, phdata->data);
	if (phdata->fork_1 != phdata->fork_2)
	{
		pthread_mutex_lock(&phdata->data->fork_mutex[phdata->fork_2]);
		ft_write(ft_time_us(), phdata->str_taken, phdata->data);
	}
	else
		usleep(phdata->data->time_to_die * 1000 + 100);
	return ;
}

void	ft_release_forks(struct s_phdata *phdata)
{
	pthread_mutex_unlock(&phdata->data->fork_mutex[phdata->fork_1]);
	if (phdata->fork_1 != phdata->fork_2)
		pthread_mutex_unlock(&phdata->data->fork_mutex[phdata->fork_2]);
	return ;
}
