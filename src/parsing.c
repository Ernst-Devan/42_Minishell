/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/05/07 08:53:01 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls
// MANAGE IF NAME FILE ARE TWO LONG



// NOT JUST SPACE BE CAREFUL TO ALL delimiter


t_table parsing(char **env) 
{
	t_table table;
	char *input;
 
	input = readline("-> ");
	if (!input)
	{
		free_lstr(env);
		printf("exit\n");
		exit(0);
	}
	input = lexer(input, env);
	if (!input)
		exit(1);
	if (init_table(&table, count_characters(input, "|")))
		free_table(table);
	if (parser(&table, env,input))
		free_table(table);
	return (table);
}
