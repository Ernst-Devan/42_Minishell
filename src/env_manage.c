/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:59:09 by njooris           #+#    #+#             */
/*   Updated: 2025/04/11 16:07:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	nb_col_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	set_env_null(char **env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		env[i] = NULL;
		i++;
	}
}

int	new_env(char **env)
{
	char	**temp;
	int		i;
	int	size_env;
	int	nb_row;

	nb_row = size_of_env(env);
	temp = malloc(nb_row + 1);
	if (!temp)
		return (1);
	set_env_null(temp, nb_row);
	i = 0;
	while (i < nb_row)
	{
		temp[i] = ft_strdup(env[i]);
		if (!temp[i])
		{
			free_lstr(temp);
			return (1);
		}
		i++; 
	}
	return (0);
}
