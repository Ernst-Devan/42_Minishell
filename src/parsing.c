/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/05/22 15:37:54 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include "exec.h"

// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls
// MANAGE IF NAME FILE ARE TWO LONG
  
// NOT JUST SPACE BE CAREFUL TO ALL delimiter
// SKIP THE SPACE BUT TOO ALL SPACE DELIMITER LIKE TAB etc

t_table parsing(t_shell *shell) 
{
	t_table table;
	char	*input;

	input = NULL;
	input = get_command(input, shell);
	input = skip_space(input, &shell->error_code);
//	if (shell->error_code)
	//	return (table);
	input = lexer(input);
	if (lexical_analyser(input) == 1)
	{
		free(input);
		table.cmd_len = 0;
		table.cmds = NULL;
		shell->error_code = 2;
		return (table);
	}
	input = manage_expand(input, *shell);
	if (init_table(&table, count_split(input, '|')))
		free_table(table);
	if (parser(&table, shell->env,input))
		free_table(table);
	return (table);
}
