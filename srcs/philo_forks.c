/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:51:06 by npirard           #+#    #+#             */
/*   Updated: 2024/01/30 13:08:56 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	take_fork(t_philo *philo, t_fork *fork, bool *has_fork)
{
	t_timeval	time;

	while (fork->last_id == philo->number)
		usleep(10);
	if (pthread_mutex_lock(&fork->mutex))
		return (1);
	gettimeofday(&time, NULL);
	fork->last_id = philo->number;
	*has_fork = true;
	print_msg(philo, &time, msg_fork_taken);
	return (0);
}

int	unlock_forks(t_philo *philo)
{
	if (philo->has_left_fork && pthread_mutex_unlock(&philo->left_fork->mutex))
		return (1);
	philo->has_left_fork = false;
	if (philo->has_right_fork
		&& pthread_mutex_unlock(&philo->right_fork->mutex))
		return (1);
	philo->has_right_fork = false;
	return (0);
}

/// @brief
/// @param philo
/// @return
int	take_both_forks(t_philo *philo)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	if (!philo->left_fork || !philo->right_fork)
	{
		print_msg(philo, &time, msg_fork_taken);
		usleep(philo->settings->meal_duration * 1000);
		return (1);
	}
	if ((philo->number % 2 == 0 && take_fork(philo, philo->left_fork,
				&philo->has_left_fork))
		|| (philo->number % 2 == 1 && take_fork(philo, philo->right_fork,
				&philo->has_right_fork)))
		return (1);
	if (philo_is_dead(philo))
		return (unlock_forks(philo), 1);
	if ((philo->number % 2 == 0 && take_fork(philo, philo->right_fork,
				&philo->has_right_fork))
		|| (philo->number % 2 == 1 && take_fork(philo, philo->left_fork,
				&philo->has_left_fork)))
		return (1);
	if (philo_is_dead(philo))
		return (unlock_forks(philo), 1);
	return (0);
}
