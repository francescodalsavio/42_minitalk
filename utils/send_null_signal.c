/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_null_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:28 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/07/07 15:55:12 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_null_signal(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			manage_client_error(str);
		return (0);
	}
	return (1);
}
