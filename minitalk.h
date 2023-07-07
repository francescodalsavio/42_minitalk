/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdal-sa <frdal-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:45:44 by francescoda       #+#    #+#             */
/*   Updated: 2023/07/07 15:56:14 by frdal-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

# define RED		"\x1b[31m"
# define BLUE	"\x1b[34m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define RESET	"\x1b[0m"

void	print_colored_string(char *color, char *s, int fd);
char	*ft_straddc(char *str, char c);
int		ft_str_isnumeric(char *str);
int		send_null_signal(int pid, char *str);
void	manage_client_error(char *str);

#endif
