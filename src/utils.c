// DONT FORGET TO ADD THE HEADER


#include "parsing.h"
#include "libft.h"

void    display_table(t_cmd *cmds)
{
    int i;

    i = 0;
    while (cmds[i].path)
    {
        ft_printf("type : %d\n", cmds[i].type);
        if (cmds[i].path != NULL)
			ft_printf("cmd  : %s\n", cmds[i].path);
        ft_printf("args : ");
        while (*cmds[i].args)
        {
            ft_printf("%s ", *cmds[i].args);
            cmds[i].args++;
        }
        ft_printf("\n\n");
        i++;
    }
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
