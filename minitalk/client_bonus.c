/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:50:46 by rabderus          #+#    #+#             */
/*   Updated: 2022/02/02 20:13:39 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_response = 0;

static void	rec_serv_response(int signum)
{
	(void)signum;
	g_response = 1;
}

static int	wait_response(void)
{
	while (g_response != 1)
	{
	}
	g_response = 0;
	return (1);
}

static int	send_string_two(int i, char *string, int pid, int count)
{
	if (string[i] & count)
	{
		if (kill(pid, SIGUSR1) == -1)
			alert("Kill error!", 0);
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			alert("Kill error!", 0);
	}
	return (count);
}

static void	send_string(int pid, char *string)
{
	int					i;
	int					num;
	int					count;
	struct sigaction	receiv;

	i = 0;
	num = ft_strlen(string);
	receiv.sa_flags = 0;
	receiv.sa_handler = rec_serv_response;
	if (sigaction(SIGUSR1, &receiv, 0) == -1
		|| sigaction(SIGUSR2, &receiv, 0) == -1)
		alert("Sigaction error!", 0);
	while (i <= num)
	{
		count = 128;
		while (count != 0)
		{
			count = send_string_two(i, string, pid, count) >> 1;
			wait_response();
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
		alert ("Wrong input!", 0);
	pid = ft_atoi(argv[1]);
	if (!pid)
		alert ("Wrong PID!", 0);
	send_string(pid, argv[2]);
}
