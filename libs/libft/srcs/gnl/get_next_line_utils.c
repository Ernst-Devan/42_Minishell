/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:12:00 by dernst            #+#    #+#             */
/*   Updated: 2025/01/30 22:25:09 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	i;

	i = 0;
	if (nmemb != 0)
	{
		if (nmemb / (INT_MAX) > size)
			return (NULL);
	}
	buffer = malloc(nmemb * size);
	if (!buffer)
	{
		buffer = NULL;
		return (buffer);
	}
	while (i < nmemb)
	{
		((char *)buffer)[i] = 0;
		i++;
	}
	return (buffer);
}

char	*gnl_ft_substr(char *s, size_t len, size_t *is_end, size_t *buffer)
{
	char	*str;
	char	*src;
	size_t	i;
	size_t	start;

	str = gnl_ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	start = 0;
	i = 0;
	len++;
	src = s + start;
	while (i < len - 1 && src[i] && len > 1)
	{
		str[i] = src[i];
		if (src[i] == '\n')
		{
			*is_end = 1;
			i++;
			break ;
		}
		i++;
	}
	*buffer = i;
	return (str);
}

void	*gnl_ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL && n == 0)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i > 0)
			((char *)dest)[--i] = ((char *)src)[--n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	((char *)dest)[i] = '\0';
	return (dest);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (free((char *)s1), NULL);
	len_s1 = gnl_ft_strlen(s1, 1);
	len_s2 = gnl_ft_strlen(s2, 1);
	str = gnl_ft_calloc((len_s1 + len_s2) + 1, sizeof(char));
	if (!str)
		return (free((char *)s1), NULL);
	j = 0;
	i = 0;
	while (s1[j] && len_s1)
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && len_s2)
		str[i++] = s2[j++];
	str[i] = '\0';
	gnl_null_free((char **)&s1);
	return (str);
}

size_t	gnl_ft_strlen(const char *str, int type)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (type == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '\n')
				return (++i);
			i++;
		}
	}
	while (str[i])
		i++;
	return (i);
}
