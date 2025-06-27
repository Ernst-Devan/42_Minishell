/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:42:33 by njooris           #+#    #+#             */
/*   Updated: 2025/06/26 11:36:45 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	len_without_slashslash(char *path)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (path[i])
	{
		while (path[i] == '/' && path[i + 1] == '/')
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*remove_consecutiv_slash(char *path)
{
	int		i;
	int		j;
	int		len;
	char	*new_path;

	len = len_without_slashslash(path);
	j = -1;
	i = -1;
	new_path = malloc(sizeof(char) * (len + 1));
	if (!new_path)
		return (NULL);
	while (path[++i] && ++j < len)
	{
		new_path[j] = path[i];
		if (path[i] == '/' && path[i + 1] == '/')
		{
			while (path[i] == '/' && path[i + 1] == '/')
				i++;
		}
	}
	new_path[len] = '\0';
	return (new_path);
}

int	len_without_dotslash(char *path)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (path[i])
	{
		if ((i > 0 && (path[i - 1] != '.' && path[i] == '.'
					&& path[i + 1] == '/')) || (i == 0 && (path[i] == '.'
					&& path[i + 1] == '/')))
		{
			while (path[i] == '.' && path[i + 1] == '/')
				i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	if ((i == 1 && path[i - 1] == '.') || (i > 1 && path[i - 2] == '/'))
		len--;
	return (len);
}

void	make_newpath_without_dotslash(int len, char *path, char *new_path)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (path[i] && j < len)
	{
		if ((i > 0 && (path[i - 1] != '.' && path[i] == '.'
					&& path[i + 1] == '/'))
			|| (i == 0 && (path[i] == '.' && path[i + 1] == '/')))
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
	free(path);
}
