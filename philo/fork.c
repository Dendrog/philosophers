/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:51:28 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:42:11 by jakim            ###   ########.fr       */
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
	printf("%ld %d has taken a fork\n", ((time->tv_sec - in_stat->time.tv_sec) * 1000 + (time->tv_usec - in_stat->time.tv_usec) / 1000), tmp->index + 1);
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
	printf("%ld %d has taken a fork\n", ((time->tv_sec - in_stat->time.tv_sec) * 1000 + (time->tv_usec - in_stat->time.tv_usec) / 1000), tmp->index + 1);
	pthread_mutex_lock(tmp->eat_check);
	if (((time->tv_sec - last_time->tv_sec) * 1000 + (time->tv_usec - last_time->tv_usec - 1000) / 1000) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	return (0);
}
