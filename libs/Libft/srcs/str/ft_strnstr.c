/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:51:47 by ernstdevan        #+#    #+#             */
/*   Updated: 2024/11/12 00:40:07 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[j])
		{
			while (big[i] == little[j] && i < len && big[i])
			{
				i++;
				j++;
			}
			if ((ft_strlen(little)) == j)
				return ((char *)big + i - j);
			i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
