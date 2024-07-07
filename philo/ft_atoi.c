/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:52:09 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 17:54:08 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	int			size;
	long long	result;

	result = 0;
	sign = 1;
	size = ft_strlen(nptr);
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r' || \
		*nptr == '\t' || *nptr == '\v' || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (long long)(*(nptr++) - '0');
		size--;
	}
	if (size)
		return (0);
	return ((int)(result * sign));
}
