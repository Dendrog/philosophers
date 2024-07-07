/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:51:48 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:59:22 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_eat(t_stats *in_stat, t_info *tmp, int flag)
{
	int	i;

	if (in_stat->must_eat != -1)
	{
		pthread_mutex_lock(tmp->eat_check);
		i = 0;
		tmp->stat->eat_count[tmp->index]++;
		while (i < in_stat->p_num)
		{
			if (tmp->stat->eat_count[i] >= in_stat->must_eat)
				flag++;
			else
				break ;
			i++;
		}
		if (flag >= in_stat->p_num)
		{
			tmp->stat->die = 2;
			pthread_mutex_unlock(tmp->eat_check);
			return (1);
		}
		pthread_mutex_unlock(tmp->eat_check);
	}
	return (0);
}

int	eating(struct timeval *last_time, t_stats *in_stat, t_info *tmp)
{
	gettimeofday(last_time, NULL);
	printf("%ld %d is eating\n", \
		timecal(*last_time, in_stat->time, 0), tmp->index + 1);
	ft_sleep(in_stat->t_eat, tmp->eat_check, *last_time, tmp);
	pthread_mutex_unlock(tmp->fk1);
	pthread_mutex_unlock(tmp->fk2);
	pthread_mutex_lock(tmp->fork_check);
	*(tmp->check1) = 0;
	*(tmp->check2) = 0;
	pthread_mutex_unlock(tmp->fork_check);
	return (all_eat(in_stat, tmp, 0));
}
