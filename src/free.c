// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include <stdio.h>

void free_lstr(char **lstr)
{
	size_t	i;
	char	*temp;
	i = 0;
	temp = NULL;
	if (lstr)
	{
		while (lstr[i])
		{
			temp = lstr[i];
			free(temp);
			i++;
		}
		free(lstr);
	}
}
 
void	free_cmds(t_table table)
{
	size_t	i;

	i = 0;
	while (i < table.cmd_len)
	{
		if (table.cmds[i].str_in)
		{
			free(table.cmds[i].str_in);
			table.cmds[i].str_in = NULL;
		}
		if (table.cmds[i].str_out)
		{
			free(table.cmds[i].str_out);
			table.cmds[i].str_out = NULL;
		}
		free(table.cmds[i].path);
		free_lstr(table.cmds[i].args);
		i++;
	}
	free(table.cmds);
	table.cmds = NULL;
}

void	free_table(t_table table)
{
	if (table.cmds)
	{
		free_cmds(table);
		table.cmds = NULL;
	}
	free(table.cmds);
}
