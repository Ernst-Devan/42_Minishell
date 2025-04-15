// DONT FORGET TO ADD THE HEADER

#include "parsing.h"

void free_lstr(char **lstr)
{
	while (*lstr)
	{
		free(*lstr);
		lstr++;
	}
	free(lstr);
}
 
void	free_cmds(t_cmd *cmd)
{
		free(cmd->path);
		free_lstr(cmd->args);
}

void	free_table(t_table *table)
{
	if (table->cmds)
	{
		free_cmds(table->cmds);
	}
	free(table->cmds);
}
