/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:27 by njooris           #+#    #+#             */
/*   Updated: 2025/05/07 13:59:56 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

char	*remove_consecutiv_slash(char *path)
{
	int	i;
	int	j;
	int	len;
	char	*new_path;

	i = 0;
	j = 0;
	len = 0;
	while (path[i])
	{
		while (path[i] == '/' && path[i + 1] == '/')
			i++;
		i++;
		len++;
	}
	i = 0;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
		return (NULL);
	while (path[i] && j < len)
	{
		new_path[j] = path[i];
		if (path[i] == '/' && path[i + 1] == '/')
		{
			while (path[i] == '/' && path[i + 1] == '/')
				i++;
		}
		i++;
		j++;
	}
	new_path[len] = '\0';
	return (new_path);
}

char	*remove_dot_slash(char *path)
{
	int	i;
	int	j;
	int	len;
	char	*new_path;

	i = 0;
	j = 0;
	len = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '/')
			i+=2;
		i++;
		len++;
	}
	if (i != 0 && path[i - 1] == '.')
		len--;
	i = 0;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
	 	return (NULL);
	while (path[i] && j < len)
	{
	 	if (path[i] == '.' && path[i + 1] == '/')
	 	{
	 		while (path[i] == '.' && path[i + 1] == '/')
	 			i += 2;
	 	}
		else
		{
			new_path[j] = path[i];
			i++;
	 		j++;
		}
	}
	new_path[len] = '\0';
	return (new_path);
}

char	*strljoin(char const *s1, char const *s2, size_t len)
{
	char	*str;
	size_t	i;

	str = malloc((len + ft_strlen(s2)) + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (*s1 && i < len)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*remove_if_dotdot(char *path)
{
	int	i;
	int	j;
	char	*temp;

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.')
		{
			j = i - 2;
			while (j != 0 && path[j] && path[j] != '/')
				j--;
			temp = path;
			path = strljoin(path, &path[i + 2], j);
			free (temp);
			i = -1;
		}
		i++;
	}
	return (path);
}