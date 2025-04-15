// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i] = (t_cmd){0};
		i++;
	}
}

int	init_table(t_table *table, int nb_cmd)
{
	int		res;
	t_cmd	*cmd;

	res = 0;
	cmd = 0;
	cmd = malloc((nb_cmd + 1) * sizeof(t_cmd));
	init_cmd(cmd, nb_cmd);
	if (!cmd)
		res = 1;
	cmd[nb_cmd] = (t_cmd){0};
	table->in = 0;
	table->out = 1;
	table->cmds = cmd;
	return (res);
}

