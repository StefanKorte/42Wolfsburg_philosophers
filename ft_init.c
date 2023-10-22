/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:18:38 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 18:17:55 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_phdata_mutex(struct s_phdata *phdata)
{
	phdata->last_eaten_mutex = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(phdata->last_eaten_mutex, NULL);
	phdata->last_eaten = 0;
}

static void	ft_init_data_mutex(struct s_data *data)
{
	int	i;

	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
	data->philos_still_eating = data->num_philo;
	data->philos_still_eating_mutex = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(data->philos_still_eating_mutex, NULL);
	return ;
}

/*
** Checks the input arguments.
** Writes an error message if wrong.
*/

static int	ft_error_num_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		write(2, &"Error:\n Arguments: number_of_philo time_to_die_(ms) ", 52);
		write(2, &"time_to_eat_(ms) time_to_sleep_(ms) ", 38);
		write(2, "[number_of_times_each_philosopher_must_eat]\n", 44);
		return (1);
	}
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2])
		|| !ft_atoi(argv[3]) || !ft_atoi(argv[4])
		|| !ft_atoi(argv[argc - 1]))
	{
		write(2, &"Error: Arguments must be integers > 0\n", 38);
		return (1);
	}
	return (0);
}

/*
** Fills the data struct with the input arguments
*/

struct s_data	*ft_init_data(int argc, char *argv[])
{
	struct s_data	*data;

	if (ft_error_num_args(argc, argv))
		return (NULL);
	data = malloc(sizeof(struct s_data));
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_meals = -1;
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	if (!data->num_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep || !data->num_meals)
	{
		write(2, &"Error: Arguments must be integers > 0\n", 38);
		free(data);
		return (NULL);
	}
	ft_init_data_mutex(data);
	return (data);
}

/*
** Fills the extra data struct for each philosopher thread.
** It contains a link to the general data struct.
*/

struct s_phdata	*ft_init_phdata(int phnum, struct s_data *data)
{
	struct s_phdata	*phdata;
	char			*num;
	char			*unit;

	phdata = malloc(sizeof(struct s_phdata));
	phdata->philo_num = phnum;
	phdata->meal_num = data->num_meals;
	phdata->data = data;
	num = ft_ultoa(phnum);
	if (!MICROSECONDS)
		unit = ft_strjoin(" ", "\0");
	else
		unit = ft_strjoin(" ", "us philosopher ");
	phdata->str_taken = ft_strjoin_3(unit, num,
			" has taken a fork\n");
	phdata->str_eating = ft_strjoin_3(unit, num, " is eating\n");
	phdata->str_sleeping = ft_strjoin_3(unit, num, " is sleeping\n");
	phdata->str_thinking = ft_strjoin_3(unit, num, " is thinking\n");
	phdata->str_died = ft_strjoin_3(unit, num, " died\n");
	phdata->fork_1 = (phnum - ((phnum + 1) % 2)) % phdata->data->num_philo;
	phdata->fork_2 = (phnum - phnum % 2) % phdata->data->num_philo;
	free(num);
	free(unit);
	ft_init_phdata_mutex(phdata);
	return (phdata);
}
