/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/04/09 12:40:22 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"

int	use_pipe(t_command command, int in, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork error in use pipe"), 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(in, 0);
		dup2(pipefd[1], 1);
		execve(command.path, command.args, NULL);
		return (perror("execve error in use pipe"), 1);
	}
	if (in != 0)
		close(in);
	if (pipefd[1] != 1)
		close(pipefd[1]);
	return (0);
}

int	ms_pipe(t_command *command)
{
	int		i;
	int		pipefd[2];
	int		in;
	int		save_in;

	i = 0;
	in = 0;
	save_in = 0;
	while (command[i].path)
	{
		if (pipe(pipefd) == -1 && command[i + 1].path)
			return (perror("pipe error"), 1);
		if (!command[i + 1].path)
			pipefd[1] = 1;
		in = save_in;
		use_pipe(command[i], in, pipefd);
		save_in = pipefd[0];
		i++;
	}
	while(wait(NULL) > -1)
	{}
	return (0);
}
