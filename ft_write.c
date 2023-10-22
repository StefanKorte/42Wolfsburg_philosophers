/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:01 by skorte            #+#    #+#             */
/*   Updated: 2022/04/16 13:01:09 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Writes the given start time and the given string with only one write call.
** Uses temporary strings, frees them afterwards.
*/

void	ft_write(unsigned long start, const char *str, struct s_data *data)
{
	char	*p_time;
	char	*p_str;

	start -= data->starttime;
	if (!MICROSECONDS)
		p_time = ft_ultoa(start / 1000);
	else
		p_time = ft_ultoa(start);
	p_str = ft_strjoin(p_time, str);
	if (ft_still_eating_get(data))
		write (1, p_str, ft_strlen(p_str));
	free(p_time);
	free(p_str);
}

void	ft_write_no_test(unsigned long start,
			const char *str, struct s_data *data)
{
	char	*p_time;
	char	*p_str;

	start -= data->starttime;
	if (!MICROSECONDS)
		p_time = ft_ultoa(start / 1000);
	else
		p_time = ft_ultoa(start);
	p_str = ft_strjoin(p_time, str);
	write (1, p_str, ft_strlen(p_str));
	free(p_time);
	free(p_str);
}
