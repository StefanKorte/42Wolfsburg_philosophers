/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:48:47 by skorte            #+#    #+#             */
/*   Updated: 2022/04/12 15:25:33 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Program name: philo
**
** Turn in files: Makefile, *.h, *.c, in directory philo/
**
** Makefile: NAME, all, clean, fclean, re
**
** Arguments:
** number_of_philosophers   time_to_die_in_ms   time_to_eat_in_ms
** time_to_sleep_in_ms   [number_of_times_each_philosopher_must_eat]
**
** External functs.:
** memset, printf, malloc, free, write,
** usleep, gettimeofday, pthread_create,
** pthread_detach, pthread_join, pthread_mutex_init,
** pthread_mutex_destroy, pthread_mutex_lock,
** pthread_mutex_unlock
**
** Libft authorized: No
**
** Description: Philosophers with threads and mutexes
*/

void	*ft_philo_thread(void *ptr)
{
	struct s_phdata	*phdata;
	struct s_data	*data;

	phdata = (struct s_phdata *)ptr;
	data = phdata->data;
	while (ft_still_eating_get(data))
	{
		ft_sleeping(phdata);
		ft_thinking(phdata);
		ft_grab_forks(phdata);
		ft_eating(phdata);
		ft_release_forks(phdata);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	struct s_data	*data;
	struct s_phdata	**phdata;
	pthread_t		**philo;
	int				i;

	data = ft_init_data(argc, argv);
	if (!data)
		return (-1);
	philo = malloc(sizeof(char *) * data->num_philo);
	phdata = malloc(sizeof(char *) * data->num_philo);
	i = 0;
	while (i < data->num_philo)
	{
		philo[i] = malloc(sizeof(pthread_t));
		phdata[i] = ft_init_phdata(i + 1, data);
		i++;
	}
	ft_begin_simulation(philo, data, phdata);
	ft_check_death(data, phdata);
	ft_end_simulation(philo, data);
	ft_free(philo, data, phdata);
	return (0);
}
