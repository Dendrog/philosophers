/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/06/29 22:50:58 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static t_stats stat;

void	arg_set(t_stats *stat, int argc, char *argv[])
{
	stat->p_num = ft_atoi(argv[1]);
	stat->t_die = ft_atoi(argv[2]);
	stat->t_eat = ft_atoi(argv[3]);
	stat->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		stat->must_eat = ft_atoi(argv[5]);
	else
		stat->must_eat = -1;
}

void	ft_sleep(int t)
{
	long long nowtime;
	long long endtime;
	struct timeval time;
	gettimeofday(&time,NULL);
	nowtime = time.tv_sec * 1000 + time.tv_usec / 1000;
	endtime = nowtime + t;
	while (1)
	{
		gettimeofday(&time,NULL);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000) - nowtime >= t)
			break ;
		else
			usleep(10);
	}
}

void	*logic(void *info)
{
	t_info *tmp;
	struct timeval time;
	t_stats in_stat;
	struct timeval last_time;
	int flag;
	flag = 0;
	in_stat.p_num = stat.p_num;
	in_stat.t_die = stat.t_die;
	in_stat.t_sleep = stat.t_sleep;
	in_stat.t_eat = stat.t_eat;
	in_stat.time.tv_usec = stat.time.tv_usec;
	in_stat.time.tv_sec = stat.time.tv_sec;
	last_time.tv_sec = in_stat.time.tv_sec;
	last_time.tv_usec = in_stat.time.tv_usec;
	tmp = (t_info *)info;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec) / 1000) >= in_stat.t_die)
			break;
		printf("%ld %d is thinking\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fk1);
		gettimeofday(&time, NULL);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fk2);
		gettimeofday(&time, NULL);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec) / 1000) >= in_stat.t_die)
		{
			pthread_mutex_unlock(tmp->fk1);
			pthread_mutex_unlock(tmp->fk2);
			break ;
		}
		gettimeofday(&last_time, NULL);
		printf("%ld %d is eating\n", ((last_time.tv_sec - in_stat.time.tv_sec) * 1000 + (last_time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		ft_sleep(in_stat.t_eat);
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		gettimeofday(&time, NULL);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec) / 1000) >= in_stat.t_die)
			break ;
		printf("%ld %d is sleeping\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		ft_sleep(in_stat.t_sleep);
		gettimeofday(&time, NULL);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec) / 1000) >= in_stat.t_die)
			break ;
	}
	gettimeofday(&time, NULL);
	printf("%ld %d is died\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
	exit(0);
}

int main(int argc, char *argv[])
{
	t_info *info;
	pthread_t *th;
	pthread_mutex_t *mt;
	int i;
	pthread_mutex_t *tmp;
	void **id;

	if (argc < 5 || argc > 6)
	{
		printf("argument Error\n");
		return (1);
	}
	else
		arg_set(&stat, argc, argv);
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
		if (i % 2 == 0)
		{
			tmp = info[i].fk2;
			info[i].fk2 = info[i].fk1;
			info[i].fk1 = tmp;
		}
		info[i].index = i;
		i++;
	}
	i = 0;
	gettimeofday(&stat.time, NULL);
	//printf("%ld %ld\n",stat.time.tv_sec, stat.time.tv_usec);
	//exit(0);
	while (i < stat.p_num)
	{
		pthread_create(&th[i], NULL, logic, (void *)&info[i]);
		//usleep(1);
		i++;
	}
	i=0;
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
