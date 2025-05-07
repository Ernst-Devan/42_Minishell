/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:54:25 by njooris           #+#    #+#             */
/*   Updated: 2025/05/07 13:56:19 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

unsigned char	ms_atoi(const char *nptr)
{
	int				x;
	long long int	val;
	int				negativ;

	val = 0;
	negativ = 1;
	x = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == ' ')
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		negativ *= 44 - nptr[x];
		x++;
	}
	while (nptr[x] != '\0' && ft_isdigit(nptr[x]))
	{
		if ((10 * val + (nptr[x] - '0')) / 10 != val)
			return (-1 * (negativ > 0));
		val = 10 * val + (nptr[x++] - '0');
	}
	return (val * negativ);
}


void	ms_exit(t_cmd cmd, char **env, t_shell shell) // donner toutes la data a exit pour tous free
{
	unsigned char	ret;

	printf("exit\n");
	ret = 0;
	free_lstr(env);
//	free_table(table);
	if (!cmd.args[1])
	{
		exit(shell.error_code);
		ret = ms_atoi(cmd.args[1]);
	}
	exit(ret);
}

void	child_exit(char **env)
{
	free_lstr(env);
//	free_table(table);
	exit(0);
}