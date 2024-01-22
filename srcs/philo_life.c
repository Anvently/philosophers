/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:24:52 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 17:26:19 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philo.h>
#include <stdio.h>
#include <string.h>

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("One philo (%p | %lu) has been created !\n", philo->thread,
		*philo->thread);
	return (NULL);
}
