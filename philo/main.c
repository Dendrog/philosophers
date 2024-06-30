/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/06/30 23:51:36 by jakim            ###   ########.fr       */
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
			usleep(100);
	}
}

/*void	time_correction(struct timeval *intime, struct timeval oritime, struct timeval nowtime, int cost)
{
	long long ori;
	long long now;
	//ori = oritime.tv_sec * 1000 + oritime.tv_usec / 1000;
	//now = nowtime.tv_sec * 1000 + nowtime.tv_usec / 1000;
	oritime.tv_usec += cost % 1000 * 1000;
	oritime.tv_sec += cost / 1000 * 1000;
	intime->tv_usec = intime->tv_usec + (oritime.tv_usec - nowtime.tv_usec);
	intime->tv_sec = intime->tv_sec + (oritime.tv_sec - nowtime.tv_sec);
} // 1000*/
//   1000000

void	*logic(void *info)
{
	t_info *tmp;
	struct timeval time;
	t_stats in_stat;
	struct timeval last_time;
	struct timeval tmp_time;
	int flag;
	int i;
	flag = 0;
	in_stat.p_num = stat.p_num;
	in_stat.t_die = stat.t_die;
	in_stat.t_sleep = stat.t_sleep;
	in_stat.t_eat = stat.t_eat;
	in_stat.must_eat = stat.must_eat;
	in_stat.time.tv_usec = stat.time.tv_usec;
	in_stat.time.tv_sec = stat.time.tv_sec;
	last_time.tv_sec = in_stat.time.tv_sec;
	last_time.tv_usec = in_stat.time.tv_usec;
	tmp = (t_info *)info;
	while (1)
	{
		if (tmp->fk1 == tmp->fk2)
			break ;
		gettimeofday(&time, NULL);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 100) / 1000) > in_stat.t_die)
			break;
		printf("%ld %d is thinking\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fk1);
		gettimeofday(&time, NULL);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fk2);
		gettimeofday(&time, NULL);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 100) / 1000) > in_stat.t_die)
		{
			pthread_mutex_unlock(tmp->fk1);
			pthread_mutex_unlock(tmp->fk2);
			break ;
		}
		gettimeofday(&last_time, NULL);
		printf("%ld %d is eating\n", ((last_time.tv_sec - in_stat.time.tv_sec) * 1000 + (last_time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		ft_sleep(in_stat.t_eat);
		//usleep(in_stat.t_eat * 1000);
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		flag = 0;
		if (in_stat.must_eat != -1)
		{
			pthread_mutex_lock(tmp->eat_check);
			i = 0;
			stat.eat_count[tmp->index]++;
			while (i < in_stat.p_num)
			{
				if (stat.eat_count[i] >= in_stat.must_eat)
					flag++;
				else
					break ;
				i++;
			}
			if (flag >= in_stat.p_num)
				exit(0) ;
			pthread_mutex_unlock(tmp->eat_check);
		}
		gettimeofday(&time, NULL);
		//time_correction(&in_stat.time, last_time, time, in_stat.t_eat);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec - 100) / 1000) > in_stat.t_die)
			break ;
		printf("%ld %d is sleeping\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		gettimeofday(&tmp_time, NULL);
		ft_sleep(in_stat.t_sleep);
		//usleep(in_stat.t_sleep * 1000);
		gettimeofday(&time, NULL);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 100) / 1000) > in_stat.t_die)
			break ;
	}
	gettimeofday(&time, NULL);
	printf("%ld %d is died\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
	exit(0);
}
// 밀리는건 처리했는데 오차가 살짝씩 생김
int main(int argc, char *argv[])
{
	t_info *info;
	pthread_t *th;
	pthread_mutex_t *mt;
	pthread_mutex_t eat_check;
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
	stat.eat_count = (int *)malloc(sizeof(int) * (stat.p_num + 5));
	i = 0;
	pthread_mutex_init(&eat_check, NULL);
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
		stat.eat_count[i] = 0;
		info[i].eat_check = &eat_check;
		info[i].index = i;
		i++;
	}
	i = 0;
	//printf("%ld %ld\n",stat.time.tv_sec, stat.time.tv_usec);
	//exit(0);
	while (i < stat.p_num)
	{
		gettimeofday(&stat.time, NULL);
		pthread_create(&th[i], NULL, logic, (void *)&info[i]);
		usleep(10);
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
