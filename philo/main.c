/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/06/12 23:49:53 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	arg_set(t_stats *stat, char *argv[])
{
	stat->p_num = ft_atoi(argv[1]);
	stat->t_die = ft_atoi(argv[2]);
	stat->t_eat = ft_atoi(argv[3]);
	stat->t_sleep = ft_atoi(argv[4]);
}

void	*logic(void *fk)
{
	
}

int main(int argc, char *argv[])
{
	t_stats stat;
	pthread_t *th;
	int	*fk;
	int i;

	if (argc != 5)
	{
		printf("argument Error\n");
		return (1);
	}
	else
		arg_set(&stat, argv);
	th = (pthread_t *)malloc(sizeof(pthread_t) * (stat.p_num + 5));
	fk = (int *)malloc(sizeof(int) * stat.p_num);
	i = 0;
	while (i < stat.p_num)
	{
		fk[i] = 1;
		i++;
	}
	i = 0;
	while (i < stat.p_num)
	{
		pthread_create(&th[i], NULL, logic, (void *)fk);
		i++;
	}
}