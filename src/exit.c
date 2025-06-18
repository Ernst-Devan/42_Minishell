/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:54:25 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 12:47:28 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

unsigned char	ms_atoi(const char *nptr, int *check)
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
		{
			*check = -1;
			return (-1 * (negativ > 0));
		}
		val = 10 * val + (nptr[x++] - '0');
	}
	return (val * negativ);
}

int	check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	unumeric_param(t_table table, char **env)
{
	write(2, "numeric argument required\n", 27);
	close_fd(table);
	free_table(table);
	free_lstr(env);
	exit (2);
}

void	unparam(t_table table, char **env, t_shell *shell)
{
	close_fd(table);
	free_lstr(env);
	free_table(table);
	exit(shell->error_code);
}

void	ms_exit(t_cmd cmd, char **env, t_shell *shell, t_table table)
{
	unsigned char	ret;
	int				check;

	check = 0;
	ret = 0;
	printf("exit\n");
	if (cmd.args[1])
		ret = ms_atoi(cmd.args[1], &check);
	if (check == -1 || (cmd.args[1] && check_args(cmd.args[1])))
		unumeric_param(table, env);
	if (cmd.args[1] && cmd.args[2])
	{
		shell->error_code = 1;
		write(2, "too many arguments\n", 19);
		return ;
	}
	if (!cmd.args[1])
		unparam(table, env, shell);
	close_fd(table);
	free_lstr(env);
	free_table(table);
	exit(ret);
}
