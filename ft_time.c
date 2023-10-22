/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:39:37 by skorte            #+#    #+#             */
/*   Updated: 2022/04/15 17:55:44 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_time_us(void)
{
	unsigned long	time_us;
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL))
		return (-1);
	time_us = (unsigned long)(time_now.tv_sec - 1649260183);
	time_us = time_us * 1000000 + (unsigned long)time_now.tv_usec;
	return (time_us);
}
