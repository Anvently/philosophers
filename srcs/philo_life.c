/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:24:52 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 18:00:16 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philo.h>
#include <stdio.h>
#include <string.h>

void	*philo_routine(void *data)
{
	t_philo			*philo;
	pthread_t		tid;

	philo = (t_philo *)data;
	tid = pthread_self();
	printf("One philo (%lu) has been created !\n", tid);
	return (NULL);
}
