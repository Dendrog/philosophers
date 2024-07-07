/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:50:40 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:46:38 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timecal(struct timeval time, struct timeval time2, int type)
{
	if (type == 0)
		return((time.tv_sec - time2.tv_sec) * 1000 + (time.tv_usec - time2.tv_usec) / 1000);
	else
		return((time.tv_sec - time2.tv_sec) * 1000 + (time.tv_usec - time2.tv_usec - 1000) / 1000);
}

void	ft_sleep(int t, pthread_mutex_t *mt, \
	struct timeval last_time, t_info *tmp)
{
	long long		nowtime;
	struct timeval	time;

	gettimeofday(&time, NULL);
	nowtime = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (1)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(mt);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec - 1000) / 1000) > tmp->stat->t_die || tmp->stat->die > 1)
		{
			tmp->stat->die++;
			if (tmp->stat->die == 1)
				printf("%ld %d is died\n", ((time.tv_sec - tmp->stat->time.tv_sec) * 1000 + (time.tv_usec - tmp->stat->time.tv_usec) / 1000), tmp->index + 1);
			pthread_mutex_unlock(mt);
			break ;
		}
		pthread_mutex_unlock(mt);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000) - nowtime >= t)
			break ;
		else
			usleep(10);
	}
}
