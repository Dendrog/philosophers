/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:53:47 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:41:25 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_set(t_stats *stat, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	stat->p_num = ft_atoi(argv[1]);
	stat->t_die = ft_atoi(argv[2]);
	stat->t_eat = ft_atoi(argv[3]);
	stat->t_sleep = ft_atoi(argv[4]);
	stat->die = 0;
	if (argc == 6)
		stat->must_eat = ft_atoi(argv[5]);
	else
		stat->must_eat = -1;
	return (0);
}

int	arg_check(t_stats *stat, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("argument Error\n");
		return (1);
	}
	else
	{
		if (arg_set(stat, argc, argv))
		{
			printf("argument Error\n");
			return (1);
		}
	}
	return (0);
}
