// DONT FORGET TO ADD THE HEADER

#include "libft.h"
#include "parsing.h"

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i].args = NULL;
		cmd[i].path = NULL;
		cmd[i].str_in = NULL;
		cmd[i].str_out = NULL;
		cmd[i].in = 0;
		cmd[i].out = 1;
		cmd[i].type = 0;
		i++;
	}
}

int	init_table(t_table *table, int nb_cmd)
{
	t_cmd	*cmd;

	cmd = calloc((nb_cmd + 2) ,sizeof(t_cmd));
	if (!cmd)
		return (1);
	table->cmd_len = nb_cmd + 1;
	init_cmd(cmd, nb_cmd + 1);
	table->cmds = cmd;
	return (0);
}
