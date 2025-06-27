/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:27 by njooris           #+#    #+#             */
/*   Updated: 2025/06/26 11:09:33 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*remove_dot_slash(char *path)
{
	int		len;
	char	*new_path;

	if (!path)
		return (NULL);
	len = len_without_dotslash(path);
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
	{
		free(path);
		return (NULL);
	}
	make_newpath_without_dotslash(len, path, new_path);
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

char	*ignore_slashslash(char *path, int j, int i)
{
	char	*temp;

	while (j >= 4 && path[j] && path[j] != '/')
		j--;
	temp = path;
	(void)i;
	path = strljoin(path, &path[i + 2], j);
	free (temp);
	return (path);
}

char	*free_and_dup(char *path)
{
	free(path);
	path = ft_strdup("PWD=/");
	return (path);
}

char	*remove_if_dotdot(char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.')
		{
			j = i - 2;
			if (j >= 4)
			{
				path = ignore_slashslash(path, j, i);
				if (!path)
					return (NULL);
				i = -1;
			}
			else
				return (free_and_dup(path));
		}
		i++;
	}
	return (path);
}
