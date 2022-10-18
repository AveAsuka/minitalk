/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:51:33 by rabderus          #+#    #+#             */
/*   Updated: 2022/01/29 18:21:43 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	miss_tab(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

static long long int	schet_itog(const char *str, int znak, int i)
{
	long long int	itog;

	itog = 0;
	while (str[i] >= '0' && str[i] <= '9')
		itog = (itog * 10) + (str[i++] - '0');
	itog = znak * itog;
	return (itog);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				znak;
	long long int	itog;

	i = 0;
	znak = 1;
	if (!str)
		return (0);
	i = miss_tab(str);
	if (str[i] == '-')
	{
		znak = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		znak = 1;
		i++;
	}
	itog = schet_itog(str, znak, i);
	if (-2147483648 <= itog && itog <= 2147483647)
		return ((int)itog);
	if (znak == -1)
		return (0);
	return (-1);
}
