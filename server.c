/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:41:03 by francescoda       #+#    #+#             */
/*   Updated: 2023/07/07 15:44:41 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(int pid, char *str)
{
	if (str)
		free(str);
	print_colored_string(RED,
		"An unexpected error occurred in the server.\n", 2);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

char	*print_string(char *message)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
	free(message);
	return (NULL);
}

void	process_byte(char *c, int *bits, char **message)
{
	if (*c)
	{
		*message = ft_straddc(*message, *c);
	}
	else
	{
		*message = print_string(*message);
	}
	*bits = 0;
	*c = 0b11111111;
}

void	handler_sigusr(int signum, siginfo_t *info, void *context)
{
	static char	c = 0b11111111;
	static int	bits = 0;
	static int	pid = 0;
	static char	*message = 0;
	int			mask;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
	{
		mask = 0b10000000 >> bits;
		c = c ^ mask;
	}
	else if (signum == SIGUSR2)
	{
		mask = 0b10000000 >> bits;
		c = c | mask;
	}
	bits++;
	if (bits == 8)
		process_byte(&c, &bits, &message);
	if (kill(pid, SIGUSR1) == -1)
		error(pid, message);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	print_colored_string(GREEN,
		"PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
