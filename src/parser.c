/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:12:40 by dernst            #+#    #+#             */
/*   Updated: 2025/05/22 12:26:59 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int insert_cmds(t_cmd *cmd, char **list_cmds, char *path) 
{
	size_t	i;
	size_t	type;
	char	**args;
	char	*path_command;

	i = 0;
	type = 0;
	args = NULL;
	while (*list_cmds != NULL) 
	{
		if (**list_cmds)
		{
			args = ft_split(*list_cmds, SEPARATOR);
			if (!args)
				return (1);
			cmd[i].args = args;
		}
		if (args && args[0])
		{
			path_command = valid_command(path, args[0], &type);
			cmd[i].path = path_command;
			if (!path_command)
				ft_printf("\n%s: command not found\n", args[0]);
			cmd[i].type = type;
			i++;
		}
		else 
		{
			cmd[i].type = 2;
			free_lstr(args);
			i++;
		}
		list_cmds++;
		
	}
  	return (0);
}

char **tokenisation(char *input) 
{
	char **splited_cmds;

	splited_cmds = split_cmd(input, '|');
	free(input);
	if (!splited_cmds)
		return (NULL);
	return (splited_cmds);
}

size_t	parser(t_table *table, char **env, char *input)
{
	char **splited_cmds;

	splited_cmds = tokenisation(input);
	manage_redirection(&table->cmds, splited_cmds);
	splited_cmds = skip_redirection(splited_cmds);
	splited_cmds = remove_quotes(splited_cmds);
	if (insert_cmds(table->cmds, splited_cmds, find_env("PATH=", env)))
		return (1);
	free_lstr(splited_cmds);
	return(0);
}
