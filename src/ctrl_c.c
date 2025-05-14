/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:12 by njooris           #+#    #+#             */
/*   Updated: 2025/05/14 16:28:09 by njooris          ###   ########.fr       */
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

int	manage_ctrl_c_var(int val)
{
	static int var;

	if (val != 3)
		var = val;
	return (var);
}

void	sig_hand(int sig)
{
	(void)sig;
	manage_ctrl_c_var(1);
	rl_done = 1;
	return ;
}

int	useless_function(void)
{
	return (0);
}

