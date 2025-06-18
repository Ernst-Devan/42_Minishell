/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:12:40 by dernst            #+#    #+#             */
/*   Updated: 2025/06/17 11:28:07 by dernst           ###   ########lyon.fr   */
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
	while (list_cmds && *list_cmds != NULL) 
	{
		if (**list_cmds)
		{
			args = ft_split(*list_cmds, SEPARATOR);
			if (!args)
				return (1);
		}
		if (args && args[0])
		{
			path_command = valid_command(path, args[0], &type);
			cmd[i].path = path_command;
			cmd[i].args = args;
			cmd[i].type = type;
			i++;
		}
		else 
		{
			cmd[i].type = 2;
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
	if (!splited_cmds)
		return(1);
	splited_cmds = manage_redirection(&table->cmds, splited_cmds);
	if (!splited_cmds)
		return (1);
	splited_cmds = remove_quotes(splited_cmds);
	if (insert_cmds(table->cmds, splited_cmds, find_env("PATH=", env)))
		return (1);
	free_lstr(splited_cmds);
	return(0);
}
