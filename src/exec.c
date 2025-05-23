/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/05/22 15:01:24 by njooris          ###   ########.fr       */
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
#include "env_manage.h"
#include <signal.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

int	exec_bin(t_table table, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork failed in exec_bin"), 1);
	if (pid == 0 && table.cmds->path)
	{
		if (dup2(table.cmds->in, STDIN_FILENO) == -1
			|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed in exec_bin");
			//free_table(table);
			exit(1);
		}
		if (execve(table.cmds->path, table.cmds->args, env) == -1)
		{
			perror("Command not found");
			//free_table(table);
			exit(1);
		}
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid failed in exec_bin"), 1);
	if (manage_ctrl_c_var(3) == 1)
		printf("\n");
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return 128 + WTERMSIG(status);
	return (status);
}

int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell)
{
	int	len;

	len = ft_strlen(cmd.args[0]);
	if (!ft_strncmp("export", cmd.args[0], len + 1))
		return (export(cmd, env));
	else if (!ft_strncmp("env", cmd.args[0], len + 1))
		return (env_builtin(*env, cmd));
	else if (!ft_strncmp("cd", cmd.args[0], len + 1))
		return (cd(cmd, env));
	else if (!ft_strncmp("echo", cmd.args[0], len + 1))
		echo(cmd);
	else if (!ft_strncmp("pwd", cmd.args[0], len + 1))
		return pwd(cmd);
	else if (!ft_strncmp("unset", cmd.args[0], len + 1))
		unset(cmd, env);
	else if (!ft_strncmp("exit", cmd.args[0], len + 1))
		ms_exit(cmd, *env, shell);
	return (0);
}

int	close_files(int nb_files)
{
	char	*str;
	char	*nb;

	nb = NULL;

	if (nb_files < 1)
		return (0);
	while (nb_files > 0)
	{
		nb_files--;
		nb = ft_itoa(nb_files);
		if (!nb)
			return (1);
		str = ft_strjoin(".EOF", nb);
		if (!str)
			return (free(nb), 1);
		free (str);
		free(nb);
	}
	return (0);
}

t_shell	exec(t_table table, char ***env, t_shell shell)
{
	int	nb_files;
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	nb_files = 0;
	manage_in(table.cmds, table, &nb_files);
	manage_out(table.cmds, table);
	if (manage_ctrl_c_var(3) == 1)
	{
		close_files(nb_files);
		shell.error_code = 130;
		return (shell);
	}
	if (table.cmd_len > 1)
	 	shell.error_code = ms_pipe(table, env, &shell);
	else if (table.cmds->type != 1 && table.cmds->path)
		shell.error_code = exec_bin(table, *env);
	else if (table.cmds->type == 1)
	{
		if (dup2(table.cmds->in, STDIN_FILENO) == -1
			|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
		{
			close_files(nb_files);
			return (perror("pid faild on exec_src_bin"), shell);
		}
		shell.error_code =  exec_builtins(table.cmds[0], env, &shell);
		dup2(save_stdin, STDIN_FILENO);
		dup2(save_stdout, STDOUT_FILENO);
	}
	close_files(nb_files);
	close(save_stdin);
	close(save_stdout);
	return (shell);
}
