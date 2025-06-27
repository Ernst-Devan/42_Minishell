/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:07:15 by njooris           #+#    #+#             */
/*   Updated: 2025/06/23 15:19:56 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "pipe.h"
#include "exec.h"
#include "libft.h"

void	manage_close_in_pipe(t_cmd command, int in, int pipefd[2])
{
	if (command.out != STDOUT_FILENO)
		close(command.out);
	if (command.in != STDIN_FILENO)
		close(command.in);
	if (in != STDIN_FILENO && in != command.in)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

int	exit_pipe(int pipefd[2], t_pack_pipe pp)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close_fd(pp.table);
	free_table(pp.table);
	free_lstr(pp.shell->env);
	exit(0);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
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
	return (last_status);
}
