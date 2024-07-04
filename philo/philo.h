/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:10 by jakim             #+#    #+#             */
/*   Updated: 2024/07/04 16:48:42 by jakim            ###   ########.fr       */
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
	int p_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int must_eat;
	int	*eat_count;
	int	*fks;
	int die;
	struct timeval time;
} t_stats;

typedef struct s_info
{
	pthread_mutex_t	*fk1;
	pthread_mutex_t *fk2;
	pthread_mutex_t	*fk_check1;
	pthread_mutex_t *fk_check2;
	pthread_mutex_t *eat_check;
	pthread_mutex_t *fork_check;
	int *check1;
	int *check2;
	int index;
} t_info;


int	ft_atoi(const char *nptr);

#endif