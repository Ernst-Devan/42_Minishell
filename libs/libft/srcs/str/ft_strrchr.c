/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:04:10 by ernstdevan        #+#    #+#             */
/*   Updated: 2024/11/09 19:25:40 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	int		last_i;

	i = 0;
	last_i = -1;
	while (s[i])
	{
		if (s[i] == c % 256)
			last_i = i;
		i++;
	}
	if (c % 256 == '\0')
		return ((char *)(&s[i]));
	if (last_i == -1)
		return (NULL);
	return ((char *)(&s[last_i]));
}
