/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:03:30 by njooris           #+#    #+#             */
/*   Updated: 2025/05/12 13:28:58 by njooris          ###   ########.fr       */
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
		if (execve(table.cmds->path, table.cmds->args, env) == -1)
			return (perror("execve faild on exec_src_bin"), 1);
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

typedef struct s_cmd2 {
  size_t	type;
  char		*path;
  char		**args;
  
  int		in;
  int		out;
  char		*str_in;
  char		*str_out;
} t_cmd2;

int	open_heredoc(char *str, char **eof)
{
	int		n;

	n = 0;
	while (str[n] && str[n] != ':')
		n++;
	*eof = malloc(sizeof(char) * (n + 1));
	if (!eof)
		return (-1);
	ft_strlcpy(*eof, str, n + 1);
	n = open(*eof, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (n);
}

int	open_in_file(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] != ':')
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

	printf("eof : %s\n", eof);
	input = readline("heredoc>");
	while (ft_strncmp(eof, input, ft_strlen(eof)))
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		input = readline("heredoc>");
	}
}

int	open_in_heredoc_cmd(t_cmd2 *cmd)
{
	int	i;
	int	fd;
	char	*eof;

	eof = NULL;
	i = 0;
	fd = 0;
	while (cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i + 2] && cmd->str_in[i] == '<' && cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == ':')
		{
			fd = open_heredoc(&cmd->str_in[i + 3], &eof);
			heredoc(fd, eof);
			// gerer l ecriture des heredoc ici
			if (fd == -1)
				return (1);
		}
		i++;
	}
	cmd->in = fd;
	return (fd);
}

int	open_in_cmd(t_cmd2 *cmd)
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
				printf("open de file\n");
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

int	manage_in(t_cmd2 *cmds)
{
	int		i;
	int		check;

	check = 0;
	i = 0;
	while (cmds[i].path)
	{
		cmds[i].in = open_in_heredoc_cmd(&cmds[i]);
		printf("in : %d\n", cmds[i].in);
		i++;
	}
	i = 0;
	while (cmds[i].path)
	{
		check = open_in_cmd(&cmds[i]);
		if (check == -1)
		{
			cmds[i].in = -1;
			perror("Error in manage in");
			return (1);
		}
		i++;
	}
	return (0);
}

t_shell	exec(t_table table, char ***env, t_shell shell)
{
	(void)env;
	(void)shell;
	(void)table;

	t_cmd2 cmds[] = {
	{
		.path = "/usr/bin/cat",
		.args = (char *[]){"cat", "-e", NULL},
		.in = 0,
		.out = 1,
		.str_in = "<<:EOF:<:2:<<:IOA:<:1",
		.str_out = ">toto"
	},
	{
		.path = "/usr/bin/cat",
		.args = (char *[]){"cat", "-e", NULL},
		.in = 0,
		.out = 1,
		.str_in = "<<:POPI:<<:PAPA",
		.str_out = ">toto"
	},
	{0}
};
	manage_in(cmds);
	printf("%d\n", cmds[0].in);
	printf("%d\n", cmds[1].in);
	//ouverture de tous les files

	// if (table.cmd_len > 1)
	//  	shell.error_code = ms_pipe(table, env, &shell);
	// else if (table.cmds->type == 0)
	// 	shell.error_code = exec_bin(table, *env);
	// else if (table.cmds->type == 1)
	// 	shell.error_code = exec_builtins(table.cmds[0], env, &shell);
	return (shell);
}
