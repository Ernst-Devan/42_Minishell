/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/04/04 17:42:44 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "parsing.h"
#include "builtins.h"
#include "libft.h"

int	exec_src_bin(t_command command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pid faild on exec_src_bin");
		return (1);
	}
	if (pid == 0)
		execve(command.path, command.args, NULL);	
	wait(NULL);
	return (0);
}

int	exec(t_command command)
{
	if (command.path)
	{
		if (exec_src_bin(command))
			return (1);
	}
	else if (ft_strncmp(command.args[0], "cd", 2)) // ligne have to change
		ms_cd(command);
	return (0);
}