/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/05/14 14:39:10 by njooris          ###   ########.fr       */
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
	
	pid = fork();
	if (pid == -1)
		return (perror("pid faild on exec_src_bin"), 1);
	if (pid == 0)
	{
		if (dup2(table.cmds->in, STDIN_FILENO) == -1
			|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
			return (perror("pid faild on exec_src_bin"), 1);
		if (execve(table.cmds->path, table.cmds->args, env) == -1)
			return (perror("execve faild on exekc_src_bin"), 1);
	}
	wait(NULL);
	if(manage_ctrl_c_var(3) == 1)
	{
		kill(SIGINT, pid);
		printf("\n");
	}
	if(manage_ctrl_c_var(3) == 1)
	{
		kill(SIGINT, pid);
		printf("\n");
	}
	return (0);
}

int	exec_builtins(t_cmd cmd, char ***env, t_shell *shell)
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
		pwd(*env);
	else if (!ft_strncmp("unset", cmd.args[0], len + 1))
		unset(cmd, env);
	else if (!ft_strncmp("exit", cmd.args[0], len + 1))
		ms_exit(cmd, *env, *shell);
	return (0);
}

int	open_heredoc(char *str, char **eof, char **name)
{
	int		n;
	static int i;

	i = 0;
	n = 0;
	*name = ft_strjoin(".EOF", ft_itoa(i));
	i++;
	while (str[n] && str[n] != ':')
		n++;
	*eof = malloc(sizeof(char) * (n + 1));
	if (!*eof)
		return (-1);
	ft_strlcpy(*eof, str, n + 1);
	n = open(*name, O_CREAT | O_RDWR, 0600);

	return (n);
}

int	open_in_file(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != ':')
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_RDONLY);
	free(new_str);
	return (n);
}

void	heredoc(int	fd, char *eof)
{
	char	*input;

	input = readline("heredoc>");
	while (ft_strncmp(eof, input, ft_strlen(eof) && input && manage_ctrl_c_var(3) != 1))
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		input = readline("heredoc>");
	}
}

int	open_in_heredoc_cmd(t_cmd *cmd, int *nb_files)
{
	int	i;
	int	fd;
	char	*eof;
	char	*name;

	eof = NULL;
	i = 0;
	fd = 0;
	while (cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i + 2] && cmd->str_in[i] == '<' && cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == ':')
		{
			fd = open_heredoc(&cmd->str_in[i + 3], &eof, &name);
			(*nb_files)++;
			heredoc(fd, eof);
			if (fd == -1)
				return (1);
			close(fd);
			fd = open_in_file(name);
		}
		i++;
	}
	cmd->in = fd;
	return (fd);
}

int	open_in_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i] == '<')
		{
			if (cmd->str_in[i + 1] && cmd->str_in[i + 2] && cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == ':')
			{
				i+=2;
				fd = cmd->in;
			}
			else if (cmd->str_in[i + 1] && cmd->str_in[i + 1] == ':')
			{
				fd = open_in_file(&cmd->str_in[i + 2]);
				if (fd == -1)
					return (-1);
			}
		}
		i++;
	}
	cmd->in = fd;
	return (fd);
}

int	manage_in(t_cmd *cmds, t_table table, int *nb_files)
{
	size_t		i;
	int		check;

	check = 0;
	i = 0;
	while (i < table.cmd_len)
	{
		cmds[i].in = open_in_heredoc_cmd(&cmds[i], nb_files);
		i++;
	}
	i = 0;
	while (i < table.cmd_len)
	{
		check = open_in_cmd(&cmds[i]);
		if (check == -1)
		{
			cmds[i].in = -1;
			perror("Error in manage in");
			return (1);
		}
		cmds[i].out = 1;
		i++;
	}
	return (0);
}
int	open_append(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != ':')
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_CREAT | O_RDWR | O_APPEND, 0600);
	free(new_str);
	return (n);
}

int	open_out_file(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != ':')
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_CREAT | O_RDWR | O_TRUNC, 0600);
	free(new_str);
	return (n);
}

int	open_out_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_out[i])
	{
		if (cmd->str_out[i] && cmd->str_out[i + 1] && cmd->str_out[i] == '>')
		{
			if (cmd->str_out[i + 1] && cmd->str_out[i + 2] && cmd->str_out[i + 1] == '>' && cmd->str_out[i + 2] == ':')
			{	
				fd = open_append(&cmd->str_out[i + 3]);
				i+=2;
			}
			else if (cmd->str_out[i + 1] && cmd->str_out[i + 1] == ':')
			{
				fd = open_out_file(&cmd->str_out[i + 2]);
				if (fd == -1)
					return (-1);
			}
		}
		i++;
	}
	if (fd == 0)
		fd++;
	cmd->out = fd;
	return (fd);
}

int	manage_out(t_cmd *cmds, t_table table)
{
	size_t		i;
	int		check;

	i = 0;
	check = 1;
	while (i < table.cmd_len)
	{
		check = open_out_cmd(&cmds[i]);
		if (check == -1)
		{
			cmds[i].in = 0;
			perror("Error in manage in");
			return (1);
		}
		i++;
	}
	return (0);
}

int	close_files(int nb_files)
{
	char	*str;
	char	*nb;

	nb = NULL;

	
	if (nb_files < 1)
		return;
	while (nb_files > 0)
	{
		nb_files--;
		nb = ft_itoa(nb_files);
		if (!nb)
			return (1);
		str = ft_strjoin("EOF", nb);
		if (!str)
			return (free(nb), 1);
		unlink(str);
		free (str);
		free(nb);
	}
	return (0);
}

t_shell	exec(t_table table, char ***env, t_shell shell)
{
	int original_stdin;
	int original_stdout;
	int	nb_files;

	nb_files = 0;
	if (!table.cmds->path)
		return (shell);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
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
	else if (table.cmds->type == 0)
		shell.error_code = exec_bin(table, *env);
	else if (table.cmds->type == 1)
	{
		if (dup2(table.cmds->in, STDIN_FILENO) == -1
			|| dup2(table.cmds->out, STDOUT_FILENO) == -1)
			{
				close_files(nb_files);
				return (perror("pid faild on exec_src_bin"), shell);
			}
		shell.error_code = exec_builtins(table.cmds[0], env, &shell);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	close_files(nb_files);
	return (shell);
}
