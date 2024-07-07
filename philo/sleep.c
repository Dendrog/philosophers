/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:52:06 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 19:01:29 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(struct timeval *time, struct timeval *last_time, \
	t_stats *in_stat, t_info *tmp)
{
	struct timeval	tmp_time;

	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (timecal(*time, *last_time, 1) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	printf("%ld %d is sleeping\n", \
		timecal(*time, in_stat->time, 0), tmp->index + 1);
	gettimeofday(&tmp_time, NULL);
	ft_sleep(in_stat->t_sleep, tmp->eat_check, *last_time, tmp);
	gettimeofday(time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	if (timecal(*time, *last_time, 1) > in_stat->t_die || tmp->stat->die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		return (1);
	}
	pthread_mutex_unlock(tmp->eat_check);
	if (in_stat->p_num % 2 == 1)
		usleep(500);
	return (0);
}
