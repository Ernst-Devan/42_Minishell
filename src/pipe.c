/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/05/15 15:12:41 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <signal.h>
#include "parsing.h"
#include "pipe.h"
#include "exec.h"
#include "libft.h"

int	use_pipe_builtins(t_cmd command, int in, int pipefd[2], char ***env, t_shell *shell) // faire la gestion d'erreur des dup2
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork error in use pipe"), 1);
	if (pid == 0)
	{
		if (pipefd[0] != STDIN_FILENO && pipefd[0] != in)
			close(pipefd[0]);
		if (command.in != STDIN_FILENO && in != command.in)
		{
			close(in);
			in = command.in;
		}
		if (command.out != STDOUT_FILENO && pipefd[1] != command.out)
		{
			close(pipefd[1]);
			pipefd[1] = command.out;
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 faild in usepipe"), 1);
		if (dup2(in, STDIN_FILENO) == -1)
			return (perror("dup2 faild in usepipe2"), 1);
		if (in != STDIN_FILENO)
			close(in);
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		if (command.type == 0)
		{ 
			execve(command.path, command.args,*env);
			return (perror("execve error in use pipe"), 1);
		}
		exec_builtins(command, env, shell);
		return (-1);
	}
	if (in != STDIN_FILENO && in != command.in)
	{
		close(in);
	}
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
	return (pid);
}

int	ms_pipe(t_table table, char ***env, t_shell *shell)
{
	size_t		i;
	int		pipefd[2];
	int		save_in;
	int		val_return;
	int		*tab_child;

	tab_child = malloc(sizeof(int) * table.cmd_len);
	i = 0;
	pipefd[0] = table.cmds[0].in;
	while (i < table.cmd_len)
	{
		save_in = pipefd[0];
		if (i + 1 < table.cmd_len && pipe(pipefd) == -1)
			return (perror("pipe error"), 1);
		if (i + 1 == table.cmd_len)
			pipefd[1] = table.cmds[i].out;
		val_return = use_pipe_builtins(table.cmds[i], save_in, pipefd, env, shell);
		tab_child[i] = val_return;
		if (val_return == 1 || val_return == -1)
		{
			free(tab_child);
			return (val_return);
		}
		i++;
	}
	while (wait(NULL) > -1)
	{
		if (manage_ctrl_c_var(3) == 1)
		{
			i = 0;
			while (i < table.cmd_len)
			{
				kill(SIGINT, tab_child[i]);
				i++;
			}
		}
	}
	free(tab_child);
	if(manage_ctrl_c_var(3) == 1)
		printf("\n");
	return (0);
}
