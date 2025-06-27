/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/06/26 13:04:44 by njooris          ###   ########.fr       */
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
#include "env_manage.h"
#include "pipe.h"

static void	exec_child_process(t_table table, char **env)
{
	if (dup2(table.cmds->in, STDIN_FILENO) == -1
		|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed in exec_bin");
		free_table(table);
		exit(free_lstr(env));
	}
	signal(SIGPIPE, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(table.cmds->path, table.cmds->args, env) == -1)
	{
		perror("Command not found");
		free_table(table);
		exit(free_lstr(env));
	}
}

int	exec_bin(t_table table, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed in exec_bin");
		return (1);
	}
	if (pid == 0 && table.cmds->path)
		exec_child_process(table, env);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid failed in exec_bin");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	exec_builtins(t_cmd cmd, t_shell *shell, t_table table, int save_std[2])
{
	int	len;

	if (!cmd.path)
		return (0);
	len = ft_strlen(cmd.args[0]);
	if (!ft_strncmp("export", cmd.args[0], len + 1))
		return (export(cmd, &shell->env));
	else if (!ft_strncmp("env", cmd.args[0], len + 1))
		return (env_builtin(shell->env, cmd));
	else if (!ft_strncmp("cd", cmd.args[0], len + 1))
		return (cd(cmd, &shell->env));
	else if (!ft_strncmp("echo", cmd.args[0], len + 1))
		echo(cmd);
	else if (!ft_strncmp("pwd", cmd.args[0], len + 1))
		return (pwd(cmd));
	else if (!ft_strncmp("unset", cmd.args[0], len + 1))
		return (unset(cmd, &shell->env));
	else if (!ft_strncmp("exit", cmd.args[0], len + 1))
	{
		close(save_std[0]);
		close(save_std[1]);
		ms_exit(cmd, shell->env, shell, table);
	}
	return (0);
}

int	manage_builtins(t_table table, t_shell *shell)
{
	int	save_std[2];
	int	ret;

	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	if (dup2(table.cmds->in, STDIN_FILENO) == -1
		|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
	{
		perror("pid faild on exec_src_bin");
		return (1);
	}
	ret = exec_builtins(table.cmds[0], shell, table, save_std);
	dup2(save_std[0], STDIN_FILENO);
	dup2(save_std[1], STDOUT_FILENO);
	close(save_std[0]);
	close(save_std[1]);
	return (ret);
}

t_shell	exec(t_table tb, t_shell sh)
{
	int	nb_files;

	nb_files = 0;
	if (manage_in(tb.cmds, tb, &nb_files) || manage_out(tb.cmds, tb))
	{
		close_fd(tb);
		sh.error_code = 1;
		return (sh);
	}
	if (manage_ctrl_c_var(3) == 1)
	{
		sh.error_code = 130;
		printf("\n");
		return (sh);
	}
	if (tb.cmd_len > 1)
		sh.error_code = ms_pipe(tb, &sh);
	else if (tb.cmds->type != 1 && tb.cmds->path)
		sh.error_code = exec_bin(tb, sh.env);
	else if (tb.cmds->type == 1)
		sh.error_code = manage_builtins(tb, &sh);
	if (manage_ctrl_c_var(3) == 1)
		printf("\n");
	close_fd(tb);
	return (sh);
}
