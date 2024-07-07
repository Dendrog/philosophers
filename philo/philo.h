/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:10 by jakim             #+#    #+#             */
/*   Updated: 2024/07/07 18:40:34 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_stats
{
	pthread_mutex_t	eat_check;
	pthread_mutex_t	fork_check;
	struct timeval	time;
	int				p_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				*eat_count;
	int				*fks;
	int				die;
}	t_stats;

typedef struct s_info
{
	pthread_mutex_t	*fk1;
	pthread_mutex_t	*fk2;
	pthread_mutex_t	*eat_check;
	pthread_mutex_t	*fork_check;
	t_stats			*stat;
	int				*check1;
	int				*check2;
	int				index;
}	t_info;

int		ft_atoi(const char *nptr);
void	mutex_prepare(pthread_mutex_t *mt, t_stats *stat, t_info *info);
void	mutex_free(t_stats *stat, pthread_mutex_t *mt);
void	join(t_stats *stat, pthread_t *th);
void	last_free(pthread_t *th, t_info *info, \
			pthread_mutex_t *mt, t_stats *stat);
int		think(t_info *tmp, struct timeval last_time, int type);
int		thinking(struct timeval *time, struct timeval *last_time, \
			t_stats *in_stat, t_info *tmp);
int		sleeping(struct timeval *time, struct timeval *last_time, \
			t_stats *in_stat, t_info *tmp);
void	*logic(void *info);
void	ft_sleep(int t, pthread_mutex_t *mt, struct timeval last_time, \
			t_info *tmp);
int		take_fork1(struct timeval *time, struct timeval *last_time, \
			t_stats *in_stat, t_info *tmp);
int		take_fork2(struct timeval *time, struct timeval *last_time, \
			t_stats *in_stat, t_info *tmp);
int		eating(struct timeval *last_time, t_stats *in_stat, t_info *tmp);
int		arg_check(t_stats *stat, int argc, char *argv[]);
int		arg_set(t_stats *stat, int argc, char *argv[]);
void	fork_set(pthread_mutex_t *mt, t_stats *stat, \
			t_info *info, int i);

#endif