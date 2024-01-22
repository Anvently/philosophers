/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:32:42 by npirard           #+#    #+#             */
/*   Updated: 2024/01/22 16:55:48 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philo.h>

int	parse_settings(t_settings *settings, char **args, int argc)
{
	if (ft_strtoi(args[0], &settings->nbr_philo))
		return (error("error parsing number of philosophers"), 1);
	if (ft_strtoi(args[1], &settings->time_to_die))
		return (error("error parsing time_to_die"), 1);
	if (ft_strtoi(args[0], &settings->meal_duration))
		return (error("error parsing meal_duration"), 1);
	if (ft_strtoi(args[0], &settings->sleep_duration))
		return (error("error parsing sleep_duration"), 1);
	if (argc == 6 && ft_strtoi(args[0], &settings->nbr_meal_to_end))
		return (error("error parsing nbr_meal_to_end"), 1);
	else if (argc == 5)
		settings->nbr_meal_to_end = -1;
	return (0);
}
