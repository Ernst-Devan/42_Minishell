/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:55 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 15:09:05 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include "stdio.h"

size_t	count_characters(char *s, char *cs)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (cs[j])
		{
			if ((s[i + 1] != SEP_TEXT) && s[i] == cs[j])
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

size_t	check_delimiter(char c, char *delimter)
{
	int		i;

	i = 0;
	while (delimter[i])
	{
		if (c == delimter[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen_c(char *str, char delimiter)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (delimiter == str[i])
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_strccat(char *dest, char *src, char c)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen_c(src, c);
	if (src == NULL || dest == NULL)
		return (0);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len);
}
