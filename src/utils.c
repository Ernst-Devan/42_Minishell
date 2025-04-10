// DONT FORGET TO ADD THE HEADER


#include "parsing.h"
#include "libft.h"

void    display_table(t_table table)
{
    int i;

    i = 0;
    while (table.cmds[i].path)
    {
        ft_printf("type : %d\n", table.cmds[i].type);
        if (table.cmds[i].path != NULL)
			ft_printf("cmd  : %s\n", table.cmds[i].path);
        ft_printf("args : ");
        while (*table.cmds[i].args)
        {
            ft_printf("%s ", *table.cmds[i].args);
            table.cmds[i].args++;
        }
        ft_printf("\n\n");
        i++;
    }
	ft_printf("in: %d\n", table.in);
	ft_printf("out: %d\n", table.out);
	ft_printf("\n");
}

int count_lstr(char **list_str)
{
    int i;

    i = 0;
    while (*list_str != NULL)
    {
        i++;
        list_str++;
    }
    return (i);
}
