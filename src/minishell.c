/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:25 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 10:42:14 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_manage.h"
#include "exec.h"
#include "parsing.h"
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <unistd.h>

static void	manage_signals(void)
{
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	rl_catch_signals = 0;
	rl_event_hook = &useless_function;
}

static char	**manage_env(char **env)
{
	char	**ms_env;

	ms_env = new_env(env);
	if (!ms_env)
	{
		write (2, "ENV fail\n", 9);
		exit(1);
	}
	return (ms_env);
}

int	minishell(char **env)
{
	t_table		table;
	t_shell		shell;
	t_cmd		cmd;
	size_t		check;

	manage_signals();
	check = 0;
	table.cmds = &cmd;
	shell.env = manage_env(env);
	shell.error_code = 0;
	while (1)
	{
		manage_ctrl_c_var(0);
		check = parsing(&shell, &table);
		if (check == 1)
			return (free_lstr(shell.env), 1);
		if (manage_ctrl_c_var(3) == 1)
			shell.error_code = 130;
		else if ((check == 0 && (table.cmd_len > 0 || table.cmds)))
			shell = exec(table, shell);
		free_table(table);
	}
	return (0);
}

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	if (minishell(env))
		return (1);
	return (0);
}
