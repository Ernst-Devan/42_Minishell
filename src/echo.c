/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:02:38 by njooris           #+#    #+#             */
/*   Updated: 2025/05/07 13:27:53 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"


void	while_echo(char **lstr)
{
	int	i;

	i = 0;
	
	while(lstr[i])
	{
		write(1, lstr[i], ft_strlen(lstr[i]));
		i++;
		if (lstr[i])
			write(1, " ", 1);
	}
}

int	echo(t_cmd command)
{
	if (!command.args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strncmp("-n", command.args[1], 3) == 0)
	{
		if (command.args[2])
			while_echo(&command.args[2]);
	}
	else
	{
		while_echo(&command.args[1]);
		write(1, "\n", 1);
	}
	return (0);
}



