// DONT FORGET TO ADD THE HEADER

#include "libft.h"
#include "parsing.h"

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i].type = 0;
		cmd[i].path = NULL;
		cmd[i].args = NULL;
		cmd[i].in = 0;
		cmd[i].out = 1;
		cmd[i].str_in = NULL;
		cmd[i].str_out = NULL;
		i++;
	}
}

int	init_table(t_table *table, int nb_cmd)
{
	table->cmds = malloc((nb_cmd + 1) * sizeof(t_cmd));
	if (!table->cmds)
		return (1);
	table->cmd_len = nb_cmd + 1;
	init_cmd(table->cmds, nb_cmd + 1);
	return (0);
}


int	init_expand(t_expand *expand)
{
	expand->i = 0;
	expand->j = 0;
	expand->buffer = ft_calloc(500, sizeof(char));
	if (!expand->buffer)
		return (1);
	return (0);
}

