/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:11:57 by rabderus          #+#    #+#             */
/*   Updated: 2022/02/02 20:16:16 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_response[2] = {};

static char	*out_str(char *fin, int z)
{
	write(1, fin, z);
	write(1, "\n", 1);
	if (fin)
		free(fin);
	fin = NULL;
	return (NULL);
}

static char	*send_symb(char *fin, char sym, int z)
{
	char	*per;
	int		i;

	i = 0;
	if (sym == '\0')
		return (out_str(fin, z - 1));
	per = (char *)malloc(sizeof(char) * (z + 1));
	if (!per)
		alert("Malloc error!", 0);
	if (z != 1)
	{
		while (fin[i])
		{
			per[i] = fin[i];
			i++;
		}
		if (fin)
			free(fin);
		fin = NULL;
	}
	per[i] = sym;
	per[++i] = '\0';
	return (per);
}

static void	sig_catch(int signum, siginfo_t *amber, void *context)
{
	static t_func	gubert;

	(void)context;
	if (gubert.bol == 0)
	{
		gubert.bol = 128;
		gubert.sym = 0;
	}
	if (signum == SIGUSR1)
	{
		gubert.sym = gubert.sym + gubert.bol;
		gubert.bol = gubert.bol >> 1;
	}
	else
		gubert.bol = gubert.bol >> 1;
	if (gubert.bol == 0)
	{
		gubert.z++;
		gubert.fin = send_symb(gubert.fin, gubert.sym, gubert.z);
		if (gubert.sym == '\0')
			gubert.z = 0;
	}
	g_response[1] = amber->si_pid;
	g_response[0] = 1;
}

int	main(void)
{
	struct sigaction	amber;

	write(1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	amber.sa_flags = SA_SIGINFO;
	amber.sa_sigaction = sig_catch;
	if (sigaction(SIGUSR1, &amber, 0) == -1
		|| sigaction(SIGUSR2, &amber, 0) == -1)
		alert("Sigaction error!", 0);
	while (1)
	{
		while (g_response[0] != 1)
		{
		}
		g_response[0] = 0;
		kill(g_response[1], SIGUSR1);
	}
}
