/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:28:48 by ernstdevan        #+#    #+#             */
/*   Updated: 2024/11/14 19:06:34 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (nmemb != 0)
	{
		if (nmemb / (INT_MAX) > size)
			return (NULL);
	}
	buffer = malloc(nmemb * size);
	if (!buffer)
		return (buffer);
	buffer = ft_memset(buffer, 0, size * nmemb);
	return (buffer);
}
