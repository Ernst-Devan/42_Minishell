/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:25 by njooris           #+#    #+#             */
/*   Updated: 2025/05/07 16:58:04 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "env_manage.h"
#include "libft.h"
#include "exec.h"
#include "parsing.h"
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>

int	minishell(char **env)
{
	t_table table;
	t_shell shell;
	char	**ms_env;

	rl_event_hook = &useless_function;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	ms_env = new_env(env);
	if (!ms_env)
		return(1);
	shell.error_code = 0;
	while (1)
	{
		manage_ctrl_c_var(0);
		shell.env = ms_env;
		table = parsing(&shell);
		if (manage_ctrl_c_var(3) != 1 && shell.error_code == 0 && table.cmd_len > 0)
			shell = exec(table, &ms_env, shell);
    }
	// ici aussi il faut tout free
	return (0);
}

int main(int ac, char **argv, char **env) {
  (void)ac;
  (void)argv;
  if (minishell(env))
    return (1);
  return (0);
}
