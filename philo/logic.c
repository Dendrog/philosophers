/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:52:55 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 19:01:18 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stat_set(t_stats *in_stat, t_stats *stat, \
	struct timeval *last_time)
{
	in_stat->p_num = stat->p_num;
	in_stat->t_die = stat->t_die;
	in_stat->t_sleep = stat->t_sleep;
	in_stat->t_eat = stat->t_eat;
	in_stat->must_eat = stat->must_eat;
	in_stat->time.tv_usec = stat->time.tv_usec;
	in_stat->time.tv_sec = stat->time.tv_sec;
	last_time->tv_sec = in_stat->time.tv_sec;
	last_time->tv_usec = in_stat->time.tv_usec;
}

static void	ending(struct timeval *time, t_stats *in_stat, t_info *tmp)
{
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	tmp->stat->die++;
	if (tmp->stat->die == 1)
		printf("%ld %d is died\n", \
		timecal(*time, in_stat->time, 0), tmp->index + 1);
	pthread_mutex_unlock(tmp->eat_check);
}

void	*logic(void *info)
{
	t_info			*tmp;
	struct timeval	time;
	t_stats			in_stat;
	struct timeval	last_time;

	tmp = (t_info *)info;
	stat_set(&in_stat, tmp->stat, &last_time);
	while (1)
	{
		if (thinking(&time, &last_time, &in_stat, tmp))
			break ;
		if (take_fork1(&time, &last_time, &in_stat, tmp))
			break ;
		if (take_fork2(&time, &last_time, &in_stat, tmp))
			break ;
		if (eating(&last_time, &in_stat, tmp))
			break ;
		if (sleeping(&time, &last_time, &in_stat, tmp))
			break ;
	}
	ending(&time, &in_stat, tmp);
	return (NULL);
}
