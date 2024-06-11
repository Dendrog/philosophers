/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:05:04 by jakim             #+#    #+#             */
/*   Updated: 2024/06/12 00:27:28 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int a = 0;

void	*print(void *t1)
{
	printf("%ld %d\n", *(pthread_t *)t1, a);
	a++;
}	

int main(int argc, char *argv[])
{
	pthread_t t1;
	pthread_t t2;
	int a;

	if (argc != 5)
	{
		printf("argument Error\n");
		return (1);
	}
	pthread_create(&t1, NULL, print, (void*)&t1);
	pthread_join(t1, NULL);
	printf("%ld", t1);
}