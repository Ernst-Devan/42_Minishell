/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/05/05 13:17:06 by njooris          ###   ########.fr       */
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

int	exec_bin(t_table table)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("pid faild on exec_src_bin"), 1);
	if (pid == 0)
	{
		if (dup2(table.cmds->in, STDIN_FILENO) == -1
			|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
			return (perror("pid faild on exec_src_bin"), 1);
		if (execve(table.cmds->path, table.cmds->args, NULL) == -1)
			return (perror("execve faild on exec_src_bin"), 1);
	}
	wait(NULL);
	return (0);
}

int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell, t_table table)
{
	int	len;

	len = ft_strlen(cmd.args[0]);
	if (!ft_strncmp("export", cmd.args[0], len + 1))
		export(cmd, env, shell);
	else if (!ft_strncmp("env", cmd.args[0], len + 1))
		print_env(*env);
	else if (!ft_strncmp("cd", cmd.args[0], len + 1))
		cd(cmd, env);
	else if (!ft_strncmp("echo", cmd.args[0], len + 1))
		echo(cmd);
	else if (!ft_strncmp("pwd", cmd.args[0], len + 1))
		pwd(cmd, *env);
	else if (!ft_strncmp("unset", cmd.args[0], len + 1))
		unset(cmd, env);
	else if (!ft_strncmp("exit", cmd.args[0], len + 1))
		ms_exit(cmd, *env, *shell, table);
	return (0);
}

t_shell	exec(t_table table, char ***env, t_shell shell)
{
	if (table.cmd_len > 1)
		shell.error_code = ms_pipe(table, env, &shell);
	else if (table.cmds->type == 0)
		shell.error_code = exec_bin(table);
	else if (table.cmds->type == 1)
		shell.error_code = exec_builtins(table.cmds[0], env, &shell, table);
	return (shell);
}
