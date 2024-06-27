/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/06/27 22:48:17 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static t_stats stat;

void	arg_set(t_stats *stat, char *argv[])
{
	stat->p_num = ft_atoi(argv[1]);
	stat->t_die = ft_atoi(argv[2]);
	stat->t_eat = ft_atoi(argv[3]);
	stat->t_sleep = ft_atoi(argv[4]);
}

void	*logic(void *info)
{
	t_info *tmp;
	struct timeval time;
	t_stats in_stat;
	in_stat.p_num = stat.p_num;
	in_stat.t_die = stat.t_die;
	in_stat.t_sleep = stat.t_sleep;
	in_stat.t_eat = stat.t_eat;

	tmp = (t_info *)info;
	while (1)
	{
		gettimeofday(&time, NULL);
		//printf("%ld%03ld %d is thinking\n", (time.tv_sec % 100), (time.tv_usec/1000), tmp->index + 1);
		printf("%ld %d is thinking\n", ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((stat.time.tv_sec * 1000) + (stat.time.tv_usec / 1000)), tmp->index + 1);
		pthread_mutex_lock(tmp->fk1);
		pthread_mutex_lock(tmp->fk2);
		gettimeofday(&time, NULL);
		//printf("%ld%03ld %d is eating\n",  (time.tv_sec % 100), (time.tv_usec/1000), tmp->index + 1);
		printf("%ld %d is eating\n",  ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((stat.time.tv_sec * 1000) + (stat.time.tv_usec / 1000)), tmp->index + 1);
		usleep(in_stat.t_eat * 1000);
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		gettimeofday(&time, NULL);
		//printf("%ld%03ld %d is sleeping\n",  (time.tv_sec % 100), (time.tv_usec/1000), tmp->index + 1);
		printf("%ld %d is sleeping\n",  ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((stat.time.tv_sec * 1000) + (stat.time.tv_usec / 1000)), tmp->index + 1);
		usleep(in_stat.t_sleep * 1000);
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_info *info;
	pthread_t *th;
	pthread_mutex_t *mt;
	int i;
	int id;

	if (argc != 5)
	{
		printf("argument Error\n");
		return (1);
	}
	else
		arg_set(&stat, argv);
	th = (pthread_t *)malloc(sizeof(pthread_t) * (stat.p_num + 5));
	info = (t_info *)malloc(sizeof(t_info) * (stat.p_num + 5));
	mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (stat.p_num + 5));
	i = 0;
	while (i < stat.p_num)
	{
		pthread_mutex_init(&mt[i], NULL);
		if (i - 1 < 0)
			info[i].fk1 = &mt[stat.p_num - 1];
		else
			info[i].fk1 = &mt[(i - 1) % stat.p_num];
		info[i].fk2 = &mt[i];
		info[i].index = i;
		i++;
	}
	i = 0;
	while (i < stat.p_num)
	{
		pthread_create(&th[i], NULL, logic, (void *)&info[i]);
		i++;
	}
	i=0;
	gettimeofday(&stat.time, NULL);
	while (i < stat.p_num)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	while (i < stat.p_num)
	{
		pthread_mutex_destroy(&mt[i]);
		i++;
	}
	free(th);
	free(info);
	free(mt);
}
