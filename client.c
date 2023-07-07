/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:40:44 by francescoda       #+#    #+#             */
/*   Updated: 2023/07/07 15:47:52 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	manage_client_error(char *str)
{
	if (str)
		free(str);
	print_colored_string(RED,
		"An unexpected error occurred.\n", 2);
	exit(EXIT_FAILURE);
}

void	send_bit_signal(char *message, int bitMask, int s_pid, int bits)
{
	if (message[bits / 8] & bitMask)
	{
		if (kill(s_pid, SIGUSR2) == -1)
			manage_client_error(message);
	}
	else if (kill(s_pid, SIGUSR1) == -1)
		manage_client_error(message);
}

int	send_next_bit(int pid, char *str)
{
	static char	*message = 0;
	static int	s_pid = 0;
	static int	bits = -1;
	static int	end = 0;
	int			bit_mask;

	if (str)
		message = ft_strdup(str);
	if (!message)
		manage_client_error(0);
	if (pid)
		s_pid = pid;
	bit_mask = 0b10000000 >> (++bits % 8);
	if (message[bits / 8] && !end)
	{
		send_bit_signal(message, bit_mask, s_pid, bits);
		return (0);
	}
	end = 1;
	if (send_null_signal(s_pid, message) == 0)
		return (0);
	free(message);
	return (1);
}

void	handler_sigusr(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_next_bit(0, 0);
	else if (signum == SIGUSR2)
	{
		print_colored_string(RED,
			"The server terminated unexpectedly.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		print_colored_string(GREEN,
			"Operation completed successfully.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_str_isnumeric(argv[1]))
	{
		print_colored_string(RED,
			"Invalid arguments provided.\n", 2);
		print_colored_string(YELLOW,
			"Please use the correct format: [./client <PID> <STR>].\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler_sigusr);
	signal(SIGUSR2, handler_sigusr);
	send_next_bit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
