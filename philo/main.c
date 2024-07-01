/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/07/01 23:17:31 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static t_stats stat;

int	arg_set(t_stats *stat, int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	stat->p_num = ft_atoi(argv[1]);
	stat->t_die = ft_atoi(argv[2]);
	stat->t_eat = ft_atoi(argv[3]);
	stat->t_sleep = ft_atoi(argv[4]);
	stat->die = 0;
	if (argc == 6)
		stat->must_eat = ft_atoi(argv[5]);
	else
		stat->must_eat = -1;
	return (0);
}

void	ft_sleep(int t, pthread_mutex_t *mt, struct timeval last_time, t_info *tmp)
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
		pthread_mutex_lock(mt);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec - 1000) / 1000) > stat.t_die || stat.die > 1)
		{
			stat.die++;
			if (stat.die == 1)
				printf("%ld %d is died\n", ((time.tv_sec - stat.time.tv_sec) * 1000 + (time.tv_usec - stat.time.tv_usec) / 1000), tmp->index + 1);
			pthread_mutex_unlock(mt);
			break;
		}
		pthread_mutex_unlock(mt);
		if ((time.tv_sec * 1000 + time.tv_usec / 1000) - nowtime >= t)
			break ;
		else
			usleep(10);
	}
}

void	think(t_info *tmp, struct timeval last_time)
{
	struct timeval time;
	gettimeofday(&time,NULL);
	while (1)
	{
		gettimeofday(&time,NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec - 1000) / 1000) > stat.t_die || stat.die > 0)
		{
			stat.die++;
			if (stat.die == 1)
				printf("%ld %d is died\n", ((time.tv_sec - stat.time.tv_sec) * 1000 + (time.tv_usec - stat.time.tv_usec) / 1000), tmp->index + 1);
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		pthread_mutex_lock(tmp->fork_check);
		if (*(tmp->check1) == 0)// && *(tmp->check2) == 0)
		{
			pthread_mutex_unlock(tmp->fork_check);
			break;
		}
		pthread_mutex_unlock(tmp->fork_check);
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
	/*
	pthread_mutex_lock(tmp->eat_check);
	if (stat.die > 0)
	{
		pthread_mutex_unlock(tmp->eat_check);
		break;
	}
	pthread_mutex_unlock(tmp->eat_check);
	*/
	while (1)
	{
		if (tmp->fk1 == tmp->fk2)
			break ;
		gettimeofday(&time, NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 1000) / 1000) > in_stat.t_die || stat.die > 0)
		{
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		printf("%ld %d is thinking\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		think(tmp, last_time);
		pthread_mutex_lock(tmp->fk1);
		gettimeofday(&time, NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (stat.die > 0)
		{
			pthread_mutex_unlock(tmp->fk1);
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fork_check);
		*(tmp->check1) = 1;
		pthread_mutex_unlock(tmp->fork_check);
		pthread_mutex_lock(tmp->fk2);
		gettimeofday(&time, NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (stat.die > 0)
		{
			pthread_mutex_unlock(tmp->fk1);
			pthread_mutex_unlock(tmp->fk2);
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		printf("%ld %d has taken a fork\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		pthread_mutex_lock(tmp->fork_check);
		*(tmp->check2) = 1;
		pthread_mutex_unlock(tmp->fork_check);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 1000) / 1000) > in_stat.t_die || stat.die > 0)
		{
			pthread_mutex_unlock(tmp->fk1);
			pthread_mutex_unlock(tmp->fk2);
			//*(tmp->check1) = 0;
			//*(tmp->check2) = 0;
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		gettimeofday(&last_time, NULL);
		printf("%ld %d is eating\n", ((last_time.tv_sec - in_stat.time.tv_sec) * 1000 + (last_time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		ft_sleep(in_stat.t_eat, tmp->eat_check, last_time, tmp);
		//usleep(in_stat.t_eat * 1000);
		pthread_mutex_unlock(tmp->fk1);
		pthread_mutex_unlock(tmp->fk2);
		pthread_mutex_lock(tmp->fork_check);
		*(tmp->check1) = 0;
		*(tmp->check2) = 0;
		pthread_mutex_unlock(tmp->fork_check);
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
			{
				stat.die = 2;
				pthread_mutex_unlock(tmp->eat_check);
				break ;
			}
			pthread_mutex_unlock(tmp->eat_check);
		}
		gettimeofday(&time, NULL);
		//time_correction(&in_stat.time, last_time, time, in_stat.t_eat);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 1000) / 1000) > in_stat.t_die || stat.die > 0)
		{
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
		printf("%ld %d is sleeping\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
		gettimeofday(&tmp_time, NULL);
		ft_sleep(in_stat.t_sleep, tmp->eat_check, last_time, tmp);
		//usleep(in_stat.t_sleep * 1000);
		gettimeofday(&time, NULL);
		pthread_mutex_lock(tmp->eat_check);
		if (((time.tv_sec - last_time.tv_sec) * 1000 + (time.tv_usec - last_time.tv_usec- 1000) / 1000) > in_stat.t_die || stat.die > 0)
		{
			pthread_mutex_unlock(tmp->eat_check);
			break;
		}
		pthread_mutex_unlock(tmp->eat_check);
	}
	gettimeofday(&time, NULL);
	pthread_mutex_lock(tmp->eat_check);
	stat.die++;
	if (flag < in_stat.p_num && in_stat.must_eat == -1 && stat.die == 1)
		printf("%ld %d is died\n", ((time.tv_sec - in_stat.time.tv_sec) * 1000 + (time.tv_usec - in_stat.time.tv_usec) / 1000), tmp->index + 1);
	pthread_mutex_unlock(tmp->eat_check);
	return (NULL);
}
// 밀리는건 처리했는데 오차가 살짝씩 생김
int main(int argc, char *argv[])
{
	t_info *info;
	pthread_t *th;
	pthread_mutex_t *mt;
	pthread_mutex_t eat_check;
	pthread_mutex_t fork_check;
	int i;
	pthread_mutex_t *tmp;
	int *sw;
	//void **id;

	if (argc < 5 || argc > 6)
	{
		printf("argument Error\n");
		return (1);
	}
	else
		if(arg_set(&stat, argc, argv))
			return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * (stat.p_num + 5));
	info = (t_info *)malloc(sizeof(t_info) * (stat.p_num + 5));
	mt = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (stat.p_num + 5));
	stat.fks = (int *)malloc(sizeof(int) * (stat.p_num + 5));
	stat.eat_count = (int *)malloc(sizeof(int) * (stat.p_num + 5));
	i = 0;
	pthread_mutex_init(&eat_check, NULL);
	pthread_mutex_init(&fork_check, NULL);
	while (i < stat.p_num)
	{
		pthread_mutex_init(&mt[i], NULL);
		if (i - 1 < 0)
		{
			info[i].fk1 = &mt[stat.p_num - 1];
			info[i].check1 = &(stat.fks[stat.p_num - 1]);
		}
		else
		{
			info[i].fk1 = &mt[(i - 1) % stat.p_num];
			info[i].check1 = &(stat.fks[(i - 1) % stat.p_num]);
		}
		info[i].fk2 = &mt[i];
		info[i].check2 = &(stat.fks[i]);
		if (i % 2 == 0)
		{
			tmp = info[i].fk2;
			info[i].fk2 = info[i].fk1;
			info[i].fk1 = tmp;
			sw = info[i].check2;
			info[i].check2 = info[i].check1;
			info[i].check1 = sw;
		}
		stat.eat_count[i] = 0;
		info[i].eat_check = &eat_check;
		info[i].fork_check = &fork_check;
		info[i].index = i;
		stat.fks[i] = 0;
		i++;
	}
	i = 0;
	//printf("%ld %ld\n",stat.time.tv_sec, stat.time.tv_usec);
	//exit(0);
	while (i < stat.p_num)
	{
		if (i % 2)
			usleep(10);
		gettimeofday(&stat.time, NULL);
		pthread_create(&th[i], NULL, logic, (void *)&info[i]);
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
