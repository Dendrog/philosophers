/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:53:04 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocs(pthread_t **th, t_info **info, \
	pthread_mutex_t **mt, t_stats *stat)
{
	*th = (pthread_t *)malloc(sizeof(pthread_t) * (stat->p_num + 5));
	*info = (t_info *)malloc(sizeof(t_info) * (stat->p_num + 5));
	*mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (stat->p_num + 5));
	stat->fks = (int *)malloc(sizeof(int) * (stat->p_num + 5));
	stat->eat_count = (int *)malloc(sizeof(int) * (stat->p_num + 5));
	if (!*th || !*info || !*mt || !stat->fks || !stat->eat_count)
	{
		free(*th);
		free(*info);
		free(*mt);
		free(stat->fks);
		free(stat->eat_count);
		return (1);
	}
	return (0);
}

void	fork_set(pthread_mutex_t *mt, t_stats *stat, \
	t_info *info, int i)
{
	pthread_mutex_init(&mt[i], NULL);
	if (i - 1 < 0)
	{
		info[i].fk1 = &mt[stat->p_num - 1];
		info[i].check1 = &(stat->fks[stat->p_num - 1]);
	}
	else
	{
		info[i].fk1 = &mt[(i - 1) % stat->p_num];
		info[i].check1 = &(stat->fks[(i - 1) % stat->p_num]);
	}
	info[i].fk2 = &mt[i];
	info[i].check2 = &(stat->fks[i]);
}

int	main(int argc, char *argv[])
{
	t_info			*info;
	pthread_t		*th;
	pthread_mutex_t	*mt;
	t_stats			stat;
	int				i;

	if (arg_check(&stat, argc, argv) || allocs(&th, &info, &mt, &stat))
		return (1);
	pthread_mutex_init(&(stat.eat_check), NULL);
	pthread_mutex_init(&(stat.fork_check), NULL);
	mutex_prepare(mt, &stat, info);
	i = 0;
	while (i < stat.p_num)
	{
		if (i % 2 == 1)
			usleep(10);
		gettimeofday(&stat.time, NULL);
		pthread_create(&th[i], NULL, logic, (void *)&info[i]);
		i++;
	}
	join(&stat, th);
	mutex_free(&stat, mt);
	last_free(th, info, mt, &stat);
}
