/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:12:40 by dernst            #+#    #+#             */
/*   Updated: 2025/06/24 15:30:08 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stddef.h>

void	insert_cmd(char **args, t_cmd **cmd, size_t *i, char *path)
{
	size_t	type;
	char	*path_command;

	type = 3;
	args = remove_quotes(args);
	args = remove_expand_list(args);
	path_command = valid_command(path, args[0], &type);
	(*cmd)[*i].path = path_command;
	(*cmd)[*i].args = args;
	(*cmd)[*i].type = type;
	*i += 1;
}

int	insert_cmds(t_cmd *cmd, char **list_cmds, char *path, size_t table_len)
{
	size_t	i;
	char	**args;

	i = 0;
	args = NULL;
	while (i < table_len)
	{
		if (*list_cmds)
		{
			if (count_words(*list_cmds, SEP) > 0)
			{
				args = ft_split(*list_cmds, SEP);
				if (!args)
					return (1);
			}
		}
		if (args && args[0])
			insert_cmd(args, &cmd, &i, path);
		else
			cmd[i++].type = 2;
		args = NULL;
		list_cmds++;
	}
	return (0);
}

char	**tokenisation(char *input)
{
	char	**splited_cmds;

	splited_cmds = split_cmd(input, '|');
	free(input);
	if (!splited_cmds)
		return (NULL);
	return (splited_cmds);
}

size_t	parser(t_table *table, char **env, char *input)
{
	char	**splited_cmds;

	splited_cmds = tokenisation(input);
	if (!splited_cmds)
	{
		free_table(*table);
		return (1);
	}
	splited_cmds = manage_redirection(&table->cmds, splited_cmds);
	if (!splited_cmds)
	{
		free_table(*table);
		return (1);
	}
	if (insert_cmds(table->cmds, splited_cmds,
			find_env("PATH=", env), table->cmd_len))
	{
		free_lstr(splited_cmds);
		free_table(*table);
		return (1);
	}
	free_lstr(splited_cmds);
	return (0);
}
