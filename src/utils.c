// DONT FORGET TO ADD THE HEADER

#include "libft.h"
#include "parsing.h"
#include <stddef.h>

void display_table(t_table table) {
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < table.cmd_len && table.cmds[i].path) 
	{
		ft_printf("type : %d\n", table.cmds[i].type);
		ft_printf("cmd  : %s\n", table.cmds[i].path);
		ft_printf("args : ");
		while (table.cmds[i].args[j])
		{
			ft_printf("%s ", table.cmds[i].args[j]);
			j++;	
		}
		j = 0;
		ft_printf("\nin  :  %d\n", table.cmds[i].in);
		ft_printf("out : %d\n", table.cmds[i].out);
		ft_printf("\n\n");
		i++;
  }
  ft_printf("\n");
}

void display_lstr(char **lstr) {
  
	size_t	i;

	i = 0;
	while (lstr[i]) 
	{
		ft_printf("%s\n",lstr[i]);
		i++;
	}
	ft_printf("\n");
}

size_t count_characters(char *s, char *cs) {
	size_t	count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (cs[j])
		{
			if (s[i] == cs[j])
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

size_t check_delimiter(char c, char *delimter) {
	int		i;

	i = 0;
	while (delimter[i])
	{
		if (c == delimter[i])
			return(1);
		i++;
	}
	return (0);
}

int count_lstr(char **lstr) {
  int i;

  i = 0;
  while (*lstr != NULL) {
    i++;
    lstr++;
  }
  return (i);
}

size_t lstrlen(char **lstr) {
	size_t count;
	size_t i;
	size_t j;

	count = 0;
	i = 0;
	j = 0;
	while (lstr[i] != NULL)
	{
		while (lstr[i][j] != '\0')
		{
			count++;
			j++;
		}
		j = 0;
		i++;
	}
  return (count);
}

int ft_strlen_c(char *str, const char *delimiter) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (str[i]) {
    while (delimiter[j]) {
      if (delimiter[j] == str[i])
        return (i);
      j++;
    }
    j = 0;
    i++;
  }
  return (i);
}

size_t ft_strccpy(char *dest, const char *src, char c) {
  int i;

  i = 0;
  while (*src && *src != c) {
    dest[i++] = *src;
    src++;
  }
  dest[i] = '\0';
  return (i);
}
