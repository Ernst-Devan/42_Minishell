/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/04/10 14:44:50 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "pipe.h"

int	use_pipe(t_cmd command, int in, int pipefd[2]) // faire la gestion d'erreur des dup2
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork error in use pipe"), 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if(dup2(in, STDIN_FILENO) == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 faild in usepipe"), 1);
		execve(command.path, command.args, NULL);
		return (perror("execve error in use pipe"), 1);
	}
	if (in != 0)
		close(in);
	if (pipefd[1] != 1)
		close(pipefd[1]);
	return (0);
}

int	ms_pipe(t_table table)
{
	int		i;
	int		pipefd[2];
	int		in;
	int		save_in;

	table.in = 0; // ligne a del
	table.out = 1; // ligne a del
	i = 0;
	save_in = table.in;
	while (table.cmds[i].path)
	{
		if (i == 0)
			in = table.in;
		if (pipe(pipefd) == -1 && table.cmds[i + 1].path)
			return (perror("pipe error"), 1);
		if (!table.cmds[i + 1].path)
			pipefd[1] = table.out;
		in = save_in;
		if (use_pipe(table.cmds[i], in, pipefd))
			return (1);
		save_in = pipefd[0];
		i++;
	}
	while (wait(NULL) > -1)
	{
	}
	return (0);
}
