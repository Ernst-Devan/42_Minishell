/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:01:12 by ernstdevan        #+#    #+#             */
/*   Updated: 2024/11/08 11:42:57 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 1)
	{
		while (i < n - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
	}
	if (n > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}
