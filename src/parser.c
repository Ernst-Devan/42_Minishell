/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:12:40 by dernst            #+#    #+#             */
/*   Updated: 2025/06/20 13:14:37 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"



char	*remove_expand_sep(char *cmd)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	if (!cmd)
		return(cmd);
	buffer = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!buffer)
		return(NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == EXPAND)
			i++;
		if (cmd[i])
			buffer[j++] = cmd[i++]; 
	}
	buffer[j] = '\0';
	free(cmd);
	return (buffer);
}

char	**remove_expand_list(char	**list_cmds)
{
	char **buffer;
	size_t	i;

	buffer = ft_calloc(count_lstr(list_cmds) + 1, sizeof(char *));
	if (!buffer)
		return (NULL);
	i = 0;
	while (list_cmds[i])
	{
		buffer[i] = remove_expand_sep(list_cmds[i]);
		i++;
	}
	buffer[i] = NULL;
	free(list_cmds);
	return (buffer);
}

int insert_cmds(t_cmd *cmd, char **list_cmds, char *path, size_t table_len) 
{
	size_t	i;
	size_t	type;
	char	**args;
	char	*path_command;
	display_lstr(list_cmds);

	i = 0;
	type = 0;
	args = NULL;
	while (i < table_len) 
	{
		if (*list_cmds)
		{
			if (count_words(*list_cmds, SEPARATOR) > 0)
	    	{
				args = ft_split(*list_cmds, SEPARATOR);
				if (!args)
					return (1);
			}
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
		args = NULL;
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
	splited_cmds = remove_expand_list(splited_cmds);
	if (insert_cmds(table->cmds, splited_cmds, find_env("PATH=", env), table->cmd_len))
	{
		free_lstr(splited_cmds);
		return (1);
	}
	free_lstr(splited_cmds);
	return(0);
}
