// DONT FORGET TO ADD THE HEADER

#include "parsing.h"

void free_lstr(char **lstr)
{
	size_t	i;

	i = 0;
	if (lstr)
	{
		while (lstr[i])
		{
			free(lstr[i]);
			i++;
		}
		free(lstr);
	}
}
 
void	free_cmds(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].path)
	{
		free(cmd[i].path);
		free_lstr(cmd[i].args);
		i++;
	}
	free(cmd);
}

void	free_table(t_table table)
{
	if (table.cmds)
		free_cmds(table.cmds);
}
