/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/06/03 13:41:40 by njooris          ###   ########.fr       */
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

void	manage_dup_pipe(t_cmd command, int pipefd[2], int in)
{
	if (!command.path)
		exit(0);
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
	if (dup2(pipefd[1], STDOUT_FILENO) == -1 || dup2(in, STDIN_FILENO) == -1)
	{
		perror("dup2 faild in usepipe");
		exit(1);
	}
	if (in != STDIN_FILENO)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

int	use_pipe(t_cmd command, int in, int pipefd[2], char ***env, t_shell *shell, t_table table) // faire la gestion d'erreur des dup2
{// FAIRE LES FREE ALL DANS LES FORKS
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork error in use pipe"), 1);
	if (pid == 0)
	{
		manage_dup_pipe(command, pipefd, in);
		if (command.type == 0)
		{ 
			execve(command.path, command.args,*env);
			perror("Commande not found");
			exit(1);
		}
		exec_builtins(command, env, shell, table);
		free_table(table);
		free_lstr(*env);
		close_fd(table);
		exit(1);
	}
	if (command.out != 1)
		close(command.out);
	if (command.in != 0)
		close(command.in);
	if (in != STDIN_FILENO && in != command.in)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
	return (pid);
}

int	waiter(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		last_status;

	status = 0;
	pid = 0;
	while (pid > -1)
	{
		pid = wait(&status);
		if (pid == last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	if (manage_ctrl_c_var(3) == 1)
		printf("\n");
	return (last_status);
}

int	ms_pipe(t_table table, char ***env, t_shell *shell)
{
	size_t		i;
	int			pipefd[2];
	int			save_in;
	int			val_return;

	i = 0;
	pipefd[0] = table.cmds[0].in;
	while (i < table.cmd_len)
	{
		save_in = pipefd[0];
		if (i + 1 < table.cmd_len && pipe(pipefd) == -1)
			return (perror("pipe error"), 1);
		if (i + 1 == table.cmd_len)
			pipefd[1] = table.cmds[i].out;
		val_return = use_pipe(table.cmds[i], save_in, pipefd, env, shell, table);
		if (val_return == 1 || val_return == -1)
			return (val_return);
		i++;
	}
	return (waiter(val_return));
}
