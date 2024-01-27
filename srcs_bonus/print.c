/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:48:18 by npirard           #+#    #+#             */
/*   Updated: 2024/01/27 12:53:50 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdio.h>

static void	print_msg_type(int action)
{
	if (action == msg_fork_taken)
		printf(" has taken a fork\n");
	else if (action == msg_is_eating)
		printf(" is eating\n");
	else if (action == msg_is_sleeping)
		printf(" is sleeping\n");
	else if (action == msg_is_thinking)
		printf(" is thinking\n");
	else if (action == msg_died)
		printf(" died\n");
	else if (action == msg_created)
		printf(" has been created\n");
	else if (action == msg_ended)
		printf(" has eaten enough\n");
}

static void	color(t_philo *philo)
{
	int	i;

	i = philo->number % 6;
	if (i == 1)
		printf(CL_1);
	else if (i == 2)
		printf(CL_2);
	else if (i == 3)
		printf(CL_3);
	else if (i == 4)
		printf(CL_4);
	else if (i == 5)
		printf(CL_5);
	else if (i == 6)
		printf(CL_6);
}

int	print_msg(t_philo *philo, t_timeval *time, int action)
{
	if (sem_wait(philo->sem_print))
		return (1);
	color(philo);
	printf("%ld : Philosopher %d",
		(time->tv_sec - philo->begin_time.tv_sec) * 1000
		+ (time->tv_usec - philo->begin_time.tv_usec) / 1000,
		philo->number);
	print_msg_type(action);
	printf(CL_RS);
	if (sem_post(philo->sem_print))
		return (1);
	return (0);
}

void	print_settings(t_settings *settings)
{
	printf("SETTINGS :\n"
		"%2$-*1$s : %3$*1$d\n"
		"%4$-*1$s : %5$*1$d\n"
		"%6$-*1$s : %7$*1$d\n"
		"%8$-*1$s : %9$*1$d\n"
		"%10$-*1$s : %11$*1$d\n\n",
		25, "Number of philosophers", settings->nbr_philo,
		"Time to die", settings->time_to_die,
		"Meal duration (ms)", settings->meal_duration,
		"Sleep duration (ms)", settings->sleep_duration,
		"Number of meals to end", settings->nbr_meal_to_end);
}
