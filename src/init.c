// DONT FORGET TO ADD THE HEADER

#include "parsing.h"

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i] = (t_cmd){0};
		cmd[i].in = 0;
		cmd[i].out = 1;
		i++;
	}
}

int	init_table(t_table *table, int nb_cmd)
{
	t_cmd	*cmd;

	cmd = malloc((nb_cmd + 1) * sizeof(t_cmd));
	if (!cmd)
		return (1);
	table->cmd_len = nb_cmd + 1;
	cmd[nb_cmd] = (t_cmd){0};
	init_cmd(cmd, nb_cmd + 1);
	table->cmds = cmd;
	return (0);
}
