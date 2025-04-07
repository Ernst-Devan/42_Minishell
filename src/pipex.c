/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/04/07 17:07:13 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct s_command {
    int  type;
    char *path;
    char **args;
} t_command;

// int	main()
// {
// 	pid_t	pid;
// 	int		pipefd[2];
// 	char	*ls = "/usr/bin/ls";
// 	char	*arg[] = {"ls" ,"-l", NULL};
// 	char	*cat = "/usr/bin/cat";
// 	char	*arg2[] = {"cat" , "-e", NULL};
// 	void	*buff;

// 	if (pipe(pipefd))
// 	{
// 		perror("pipe faild on pipe");
// 		return (1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("pid faild on pipe");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
//         dup2(pipefd[1], 1);
// 		if (execve(ls, arg, NULL) == -1)
// 		{
// 			perror("execve faild on pipe");
// 			return (1);
// 		}
// 	}
// 	close(pipefd[1]);
// 	wait(NULL);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("pid faild on pipe");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(pipefd[0], 0);
// 		if (execve(cat, arg2, NULL))
// 		{
// 			perror("execve faild on pipe");
// 			return (1);
// 		}
// 	}
// 	close(pipefd[0]);
// 	wait(NULL);
// 	return (0);
// }

int	write_in_pipe(int *pipefd, t_command command)
{
	pid_t	pid;

	if (pipe(pipefd))
	{
		perror("pipe faild on pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("pid faild on pipe");
		return (1);
	}
	if (pid == 0)
	{
        dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		if (execve(command.path, command.args, NULL) == -1)
		{
			perror("execve faild on pipe");
			return (1);
		}
	}
		close(pipefd[1]);
		wait(NULL);
	return (0);
}

int	read_in_pipe(int *pipefd, t_command command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pid faild on pipe");
		return (1);
	}
	if (pid == 0)
	{
        dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		if (execve(command.path, command.args, NULL))
		{
			perror("execve faild on pipe");
			return (1);
		}
	}
	close(pipefd[0]);
	wait(NULL);
	return (0);
}

int	ms_pipe(t_command command)
{
	int		pipefd[2];

	if (pipe(pipefd))
	{
		perror("pipe faild on pipe");
		return (1);
	}
	write_in_pipe(pipefd, command);
	read_in_pipe(pipefd, command);
	return (0);
}