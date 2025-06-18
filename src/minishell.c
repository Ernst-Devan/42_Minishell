/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:25 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 15:41:20 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_manage.h"
#include "exec.h"
#include "parsing.h"
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <unistd.h>

int	minishell(char **env)
{
	t_table		table;
	t_shell		shell;
	char		**ms_env;
	t_cmd		cmd;
	size_t		check;

	check = 0;
	table.cmds = &cmd; rl_catch_signals = 0;
	rl_event_hook = &useless_function;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	ms_env = new_env(env);
	if (!ms_env)
	{
		write (2, "ENV fail\n", 9);
		return(1);
	}
	shell.error_code = 0;
	while (1)
	{
		manage_ctrl_c_var(0);
		shell.env = ms_env;
		check = parsing(&shell, &table);
		if (check == 1)
		{
			free_lstr(ms_env);
			return (1);
		}
		if ((check == 0 && (manage_ctrl_c_var(3) != 1 && (table.cmd_len > 0 || table.cmds))))
		{
			shell = exec(table, &ms_env, shell);
			free_table(table);
		}
    }
	return (0);
}

int main(int ac, char **argv, char **env) {
  (void)ac;
  (void)argv;
  if (minishell(env))
    return (1);
  return (0);
}
