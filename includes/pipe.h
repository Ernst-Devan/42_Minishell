/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:43:27 by njooris           #+#    #+#             */
/*   Updated: 2025/06/23 14:09:43 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H 
# define PIPE_H

# include "parsing.h"

typedef struct s_pack_pipe
{
	t_table	table;
	t_shell	*shell;
}	t_pack_pipe;

int		use_pipe(t_cmd command, int in, int pipefd[2], t_pack_pipe pp);
int		ms_pipe(t_table table, t_shell *shell);
void	manage_close_in_pipe(t_cmd command, int in, int pipefd[2]);
int		exit_pipe(int pipefd[2], t_pack_pipe pp);
void	reset_signals(void);
int		waiter(pid_t last_pid);

#endif