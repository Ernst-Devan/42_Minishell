/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:23:44 by ernstdevan        #+#    #+#             */
/*   Updated: 2024/11/15 13:29:41 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (check_set(s1[start], set) == 1 && s1[start])
		start++;
	while (check_set(s1[end], set) == 1 && end >= 0)
		end--;
	if (start > end)
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	result = malloc((end - start) + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 2);
	return (result);
}
