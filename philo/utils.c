/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:54:59 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:58:12 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_prepare(pthread_mutex_t *mt, t_stats *stat, t_info *info)
{
	int				i;
	int				*sw;
	pthread_mutex_t	*tmp;

	i = 0;
	while (i < stat->p_num)
	{
		fork_set(mt, stat, info, i);
		if (i % 2 == 0)
		{
			tmp = info[i].fk2;
			info[i].fk2 = info[i].fk1;
			info[i].fk1 = tmp;
			sw = info[i].check2;
			info[i].check2 = info[i].check1;
			info[i].check1 = sw;
		}
		stat->eat_count[i] = 0;
		info[i].eat_check = &(stat->eat_check);
		info[i].fork_check = &(stat->fork_check);
		info[i].index = i;
		stat->fks[i] = 0;
		info[i].stat = stat;
		i++;
	}
}

void	mutex_free(t_stats *stat, pthread_mutex_t *mt)
{
	int	i;

	i = 0;
	while (i < stat->p_num)
	{
		pthread_mutex_destroy(&mt[i]);
		i++;
	}
	pthread_mutex_destroy(&(stat->eat_check));
	pthread_mutex_destroy(&(stat->fork_check));
}

void	join(t_stats *stat, pthread_t *th)
{
	int	i;

	i = 0;
	while (i < stat->p_num)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

void	last_free(pthread_t *th, t_info *info, \
	pthread_mutex_t *mt, t_stats *stat)
{
	free(th);
	free(info);
	free(mt);
	free(stat->eat_count);
	free(stat->fks);
}
