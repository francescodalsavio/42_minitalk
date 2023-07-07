/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francescodalsavio <francescodalsavio@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:23:52 by frdal-sa          #+#    #+#             */
/*   Updated: 2023/07/01 14:34:00 by francescoda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	str = malloc(size * nmemb);
	if (!str)
		return (NULL);
	ft_bzero(str, size * nmemb);
	return (str);
}
