/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 01:19:32 by skorte            #+#    #+#             */
/*   Updated: 2021/08/21 15:57:11 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** ft_ultoa Parameters:
** #1. the unsigned long integer to convert.
** Return value The string representing the unsigned integer. NULL if the
** allocation fails.
** External functs. malloc
** Description: Allocates (with malloc(3)) and returns a string
** representing the number received as an argument.
** Negative numbers will not be handled.
*/

static int	ft_digits(unsigned long n)
{
	int	digits;

	digits = 0;
	if (!n)
		digits ++;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_ultoa(unsigned long n)
{
	char	*str;
	int		digits;

	digits = ft_digits(n);
	str = (char *)malloc (digits * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	str[digits] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[digits - 1] = (n % 10) + '0';
		digits--;
		n = n / 10;
	}
	return (str);
}

/*
** The atoi() function converts the string pointed to by nptr to int.
** The string may begin with an arbitrary amount of white space
** followed by a single optional '+' or '-' sign.
** If negative, then the output is 0.
**
** The remainder of the string is converted to a long value in the
** obvious manner, stopping at the first character which is not a
** valid digit.
** If the end of the string is not reached (stopped at non-numeric char)
** or the number is out of integer range, 0 will be returned.
*/

static char	*ft_skip(char *nptr)
{
	while (1)
	{
		if (*nptr == ' ' || *nptr == '\t' || *nptr == '\v')
			nptr++;
		else if (*nptr == '\r' || *nptr == '\n' || *nptr == '\f')
			nptr++;
		else
			break ;
	}
	if (*nptr == '+')
		nptr++;
	return (nptr);
}

int	ft_atoi(char *nptr)
{
	long int	output_int;

	nptr = ft_skip(nptr);
	output_int = 0;
	if (*nptr == '-')
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{	
		output_int = output_int * 10 + *nptr - '0';
		if (output_int > 2147483647)
		{
			output_int = 0;
			break ;
		}
		nptr++;
	}
	if (*nptr != 0)
		output_int = 0;
	return ((int)output_int);
}
