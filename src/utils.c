// DONT FORGET TO ADD THE HEADER

#include "libft.h"
#include "parsing.h"
#include <stddef.h>

void display_table(t_table table) 
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < table.cmd_len) 
	{
		ft_printf("\ntype : %d\n", table.cmds[i].type);
		ft_printf("cmd  : %s\n", table.cmds[i].path);
		ft_printf("args : ");
		if (!table.cmds[i].args[0])
			ft_printf("(null)");
		while (table.cmds[i].args && table.cmds[i].args[j])
		{
			ft_printf("%s ", table.cmds[i].args[j]);
			j++;	
		}
		j = 0;
		ft_printf("\nin : %d\n", table.cmds[i].in);
		ft_printf("out : %d\n", table.cmds[i].out);
		ft_printf("str_in : %s\n", table.cmds[i].str_in);
		ft_printf("str_out : %s\n", table.cmds[i].str_out);
		i++;
  }
  ft_printf("\n");
}

void display_lstr(char **lstr) {
  
	size_t	i;

	i = 0;
	if (!lstr[i])
		ft_printf(" (null)\n");
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

char *skip_characters(char *input, char c) {
  while (*input == c && *input)
    input++;
  return (input);
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

int ft_strlen_c(char *str, char delimiter) {
  int i;

  i = 0;
  while (str[i]) 
	{
		if (delimiter == str[i])
			return (i);
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

size_t	ft_strccat(char *dest, char *src, char c)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen_c(src, c);
	if (src == NULL || dest == NULL)
		return (0);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len);
}
