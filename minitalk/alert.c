/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:49:53 by rabderus          #+#    #+#             */
/*   Updated: 2022/01/29 18:52:20 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	alert(char *text, int pid)
{
	int	i;

	i = 0;
	while (text[i])
		i++;
	write(1, text, i);
	write(1, "\n", 1);
	if (pid > 0)
		kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}
