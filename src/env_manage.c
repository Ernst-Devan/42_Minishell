/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:59:09 by njooris           #+#    #+#             */
/*   Updated: 2025/04/14 17:04:44 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "libft.h"

int	size_of_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char **new_env(char **env)
{
	char	**temp;
	int		i;
	int		nb_row;

	nb_row = size_of_env(env);
	temp = malloc(sizeof(char *) * (nb_row + 1));
	if (!temp)
		return (NULL);
	temp[nb_row] = NULL;
	i = 0;
	while (i < nb_row)
	{
		temp[i] = ft_strdup(env[i]);
		if (!temp[i])
		{
			free_lstr(temp);
			return (NULL);
		}
		i++; 
	}
	return (temp);
}
