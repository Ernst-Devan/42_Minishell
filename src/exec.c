/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/04/15 11:11:40 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "parsing.h"
#include "builtins.h"
#include "libft.h"
#include "exec.h"
#include "pipe.h"

int	exec_bin(t_table table)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid faild on exec_src_bin"), 1);
	if (pid == 0)
	{
		if(dup2(table.in, STDIN_FILENO) == -1 || dup2(table.out, STDOUT_FILENO) == -1)
			return (perror("pid faild on exec_src_bin"), 1);
		if (execve(table.cmds->path, table.cmds->args, NULL) == -1)
			return (perror("execve faild on exec_src_bin"), 1);
	}
	wait(NULL);
	return (0);
}

int	exec(t_table table, char ***env)
{
	if(export(table, env))
		return (1);
	// (void)env;
	// if (table.cmds[1].path)
	// 	return (ms_pipe(table));
	// else if (ft_strncmp(table.cmds->path, "cd", 2) == 0)
	// 	return (ms_cd(*table.cmds));
	// else
	// 	return (exec_bin(table));
	return (0);
}
