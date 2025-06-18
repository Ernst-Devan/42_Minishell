/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 13:34:48 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "exec.h"
#include "builtins.h"
#include "env_manage.h"
#include "pipe.h"

static void	exec_child_process(t_table table, char **env)
{
	if (dup2(table.cmds->in, STDIN_FILENO) == -1
		|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed in exec_bin");
		exit(1);
	}
	signal(SIGPIPE, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(table.cmds->path, table.cmds->args, env) == -1)
	{
		perror("Command not found");
		free_table(table);
		free_lstr(env);
		exit(1);
	}
}

int	exec_bin(t_table table, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork failed in exec_bin"), 1);
	if (pid == 0 && table.cmds->path)
		exec_child_process(table, env);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid failed in exec_bin"), 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell, t_table table)
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
		return (pwd(cmd));
	else if (!ft_strncmp("unset", cmd.args[0], len + 1))
		return (unset(cmd, env));
	else if (!ft_strncmp("exit", cmd.args[0], len + 1))
		ms_exit(cmd, *env, shell, table);
	return (0);
}

int	manage_builtins(t_table table, char ***env, t_shell *shell)
{
	int	save_stdin;
	int	save_stdout;
	int	ret;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (dup2(table.cmds->in, STDIN_FILENO) == -1
		|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
		return (perror("pid faild on exec_src_bin"), 1);
	ret = exec_builtins(table.cmds[0], env, shell, table);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
	return (ret);
}

t_shell	exec(t_table table, char ***env, t_shell shell)
{
	int	nb_files;

	nb_files = 0;
	if (manage_in(table.cmds, table, &nb_files)
		|| manage_out(table.cmds, table))
	{
		shell.error_code = 1;
		return (shell);
	}
	if (manage_ctrl_c_var(3) == 1)
	{
		printf("^C\n");
		shell.error_code = 130;
		return (shell);
	}
	if (table.cmd_len > 1)
		shell.error_code = ms_pipe(table, &shell);
	else if (table.cmds->type != 1 && table.cmds->path)
		shell.error_code = exec_bin(table, *env);
	else if (table.cmds->type == 1)
		shell.error_code = manage_builtins(table, env, &shell);
	if (manage_ctrl_c_var(3) == 1)
		printf("\n");
	close_fd(table);
	return (shell);
}
