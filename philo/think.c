/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:49:14 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 19:02:06 by jakim            ###   ########.fr       */
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
		if (timecal(time, last_time, 1) > \
			tmp->stat->t_die || tmp->stat->die > 0)
		{
			tmp->stat->die++;
			if (tmp->stat->die == 1)
				printf("%ld %d is died\n", \
				timecal(time, tmp->stat->time, 0), tmp->index + 1);
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
	if (timecal(*time, *last_time, 1) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d is thinking\n", \
		timecal(*time, in_stat->time, 0), tmp->index + 1);
	if (think(tmp, *last_time, 1))
		return (1);
	return (0);
}
