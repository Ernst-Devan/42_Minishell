// DONT FORGET TO ADD THE HEADER

#include "libft.h"
#include "parsing.h"

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i] = (t_cmd){0};
		cmd[i].out = 1;
		i++;
	}
}

int	init_table(t_table *table, int nb_cmd)
{
	table->cmds = calloc((nb_cmd + 1) ,sizeof(t_cmd));
	if (!table->cmds)
		return (1);
	table->cmd_len = nb_cmd + 1;
	init_cmd(table->cmds, nb_cmd + 1);
	return (0);
}
