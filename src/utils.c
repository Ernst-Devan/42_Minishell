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

void	display_lstr(char **lstr)
{
	while(*lstr)
	{
		ft_printf("%s\n", *lstr);
		lstr++;
	}
	ft_printf("\n");
}

int	count_character(char *s, char c)
{
	int i;

	i = 0;
	while(*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

size_t check_delimiter(char c)
{
    char delimiter[7] = {" <>|&\0"};
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (c == delimiter[i])
            return (1);
        i++;
    }
    return (0);
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

int ft_strlen_c(char *str, const char *delimiter)
{
    int	i;
	int	j;

    i = 0;
	j = 0;
    while (str[i])
	{
		while (delimiter[j])
		{
			if (delimiter[j] == str[i])
				return(i);
			j++;
		}
		j = 0;
		i++;
	}
    return (i);
}
