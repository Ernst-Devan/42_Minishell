/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:20:20 by njooris           #+#    #+#             */
/*   Updated: 2025/04/16 14:40:09 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//! Secure if the env is empty

#include "libft.h"
#include <stdio.h>

char *find_env(char *str, char **env)
{
	int	count;
	int	i;

	i = 0;
	count = ft_strlen(str);
	while (env[i])
    {
		if (ft_strncmp(str, env[i], count) == 0)
			return (env[i] + count + 1);
		i++;
    }
	return (NULL);
}

int		can_print_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!can_print_env(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
}
