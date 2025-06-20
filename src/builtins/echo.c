/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:02:38 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 11:08:30 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "exec.h"
#include "libft.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	while_echo(char **lstr)
{
	int	i;

	i = 0;
	while (lstr[i])
	{
		write(1, lstr[i], ft_strlen(lstr[i]));
		i++;
		if (lstr[i])
			write(1, " ", 1);
	}
}

int	echo(t_cmd command)
{
	int	i;

	i = 1;
	if (!command.args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (command.args[1][1] && command.args[1][0] == '-'
		&& !check_n(&command.args[1][1]))
	{
		while (command.args[i] && command.args[i][0] && command.args[i][1]
		&& command.args[i][1] && command.args[i][0] == '-'
		&& !check_n(&command.args[i][1]))
			i++;
		if (command.args[i])
			while_echo(&command.args[i]);
	}
	else
	{
		while_echo(&command.args[1]);
		write(1, "\n", 1);
	}
	return (0);
}
