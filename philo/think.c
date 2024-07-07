/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:49:14 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:40:51 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_prepare(int **comp, int **check, int type, t_info *tmp)
{
	if (type == 1)
	{
		*comp = NULL;
		*check = tmp->check1;
	}
	else
	{
		*comp = tmp->check1;
		*check = tmp->check2;
	}
}

static int	able_fork(t_info *tmp, int *check, int *comp)
{
	pthread_mutex_lock(tmp->fork_check);
	if (*(check) == 0 && check != comp)
	{
		*(check) = 1;
		pthread_mutex_unlock(tmp->fork_check);
		return (0);
	}
	pthread_mutex_unlock(tmp->fork_check);
	return (1);
}

int	think(t_info *tmp, struct timeval last_time, int type)
{
	struct timeval	time;
	int				*check;
	int				*comp;

	think_prepare(&comp, &check, type, tmp);
	while (1)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec - 1000) / 1000) > tmp->stat->t_die || tmp->stat->die > 0)
		{
			tmp->stat->die++;
			if (tmp->stat->die == 1)
				printf("%ld %d is died\n", ((time.tv_sec - tmp->stat->time.tv_sec) * 1000 + (time.tv_usec - tmp->stat->time.tv_usec) / 1000), tmp->index + 1);
			pthread_mutex_unlock(tmp->eat_check);
			return (1);
		}
		pthread_mutex_unlock(tmp->eat_check);
		if (!able_fork(tmp, check, comp))
			return (0);
	}
}

int	thinking(struct timeval *time, struct timeval *last_time, \
	t_stats *in_stat, t_info *tmp)
{
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (((time->tv_sec - last_time->tv_sec) * 1000 + (time->tv_usec - last_time->tv_usec - 1000) / 1000) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d is thinking\n", ((time->tv_sec - in_stat->time.tv_sec) * 1000 + (time->tv_usec - in_stat->time.tv_usec) / 1000), tmp->index + 1);
	if (think(tmp, *last_time, 1))
		return (1);
	return (0);
}
