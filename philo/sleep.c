/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:52:06 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:43:56 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(struct timeval *time, struct timeval *last_time, \
	t_stats *in_stat, t_info *tmp)
{
	struct timeval	tmp_time;

	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (((time->tv_sec - last_time->tv_sec) * 1000 + (time->tv_usec - last_time->tv_usec - 1000) / 1000) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d is sleeping\n", ((time->tv_sec - in_stat->time.tv_sec) * 1000 + (time->tv_usec - in_stat->time.tv_usec) / 1000), tmp->index + 1);
	gettimeofday(&tmp_time, NULL);
	ft_sleep(in_stat->t_sleep, tmp->eat_check, *last_time, tmp);
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (((time->tv_sec - last_time->tv_sec) * 1000 + (time->tv_usec - last_time->tv_usec - 1000) / 1000) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	if (in_stat->p_num % 2 == 1)
		usleep(500);
	return (0);
}
