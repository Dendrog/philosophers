/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:51:28 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:59:34 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork1(struct timeval *time, struct timeval *last_time, \
	t_stats *in_stat, t_info *tmp)
{
	pthread_mutex_lock(tmp->fk1);
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d has taken a fork\n", \
		timecal(*time, in_stat->time, 0), tmp->index + 1);
	if (think(tmp, *last_time, 2))
	{
		pthread_mutex_unlock(tmp->fk1);
		return (1);
	}
	return (0);
}

int	take_fork2(struct timeval *time, struct timeval *last_time, \
	t_stats *in_stat, t_info *tmp)
{
	pthread_mutex_lock(tmp->fk2);
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d has taken a fork\n", \
		timecal(*time, in_stat->time, 0), tmp->index + 1);
	pthread_mutex_lock(tmp->eat_check);
	if (timecal(*time, *last_time, 1) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	return (0);
}
