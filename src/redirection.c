// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>


// We can too send the command if there are not valid
// and same if just have not command

char	*ft_ignore_str(char *str, char *ignore)
{
	char	*cpy_str;
	char	*temp;
	size_t	i;

	cpy_str = str;
	i = 0;
	temp = malloc(ft_strlen(str) + 1);
	while (*cpy_str)
	{
		if (*cpy_str == *ignore)
		{
			if (!ft_strncmp(cpy_str, ignore, ft_strlen(ignore)))
				cpy_str += ft_strlen(ignore);
		}
		if (!*cpy_str)
			break;
		temp[i] = *cpy_str;
		i++;
		cpy_str++;
	}
	temp[i] = '\0';
	free(str);
	return (temp);
}

char	*remove_quote(char *str)
{
	size_t	i;
	size_t	j;
	char	*temp;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	temp = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (inside_quote(str[i], &quote) > 1)
		{
			i++;
			if (str[i] && str[i] == quote)
			{
				quote = 0;
				i++;
			}
		}
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	free(str);
	return (temp);
}

char **skip_redirection(char **split_cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;
	char	quote;
	
	i = 0;
	j = 0;
	quote = 0;
	while (split_cmd[i])
	{
		k = 0;
		temp = malloc((ft_strlen(split_cmd[i]) + 1 ) * sizeof(char));
		while(split_cmd[i][j])
		{
			inside_quote(split_cmd[i][j], &quote);
			if (quote == 0)
			{
				if (split_cmd[i][j] == '>' || split_cmd[i][j] == '<')
				{
					j += ft_strlen_c(&split_cmd[i][j], SEPARATOR);
					j++;
					j += ft_strlen_c(&split_cmd[i][j], SEPARATOR);
				}
			}
			if (!split_cmd[i][j])
				break;
			temp[k] = split_cmd[i][j];
			k++;
			j++;
		}
		j = 0;
		temp[k] = '\0';
		free(split_cmd[i]);
		split_cmd[i] = temp;
		i++;
	}
	return (split_cmd);
}

//!!! BUGS WHEM THE REDIRECTION ARE TOO LONG 
// Patch the bug with adding the name max of a redirection
// ADDING max for all other category like Path_max Name_max Command_max etc..


char	*redirection_in(char *in, char **split_cmd, size_t *i, size_t *j, char *quote)
{
		if (split_cmd[*i][*j] == '<')
		{
			(*j) += ft_strccat(in, &split_cmd[*i][*j], SEPARATOR);
			ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd[*i]) + 1);
			inside_quote(split_cmd[*i][*j], quote);
			if (*quote != 0)
				ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd[*i]) + 1);
			(*j)++;
			(*j) += ft_strccat(in, &split_cmd[*i][*j], SEPARATOR);
			ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd[*i] + 1));
	}
	return (in);
}

char	*redirection_out(char *out, char **split_cmd, size_t *i, size_t *j, char *quote)
{
	if (split_cmd[*i][*j] == '>')
	{
			(*j) += ft_strccat(out, &split_cmd[*i][*j], SEPARATOR);
			ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd[*i]) + 1);
			inside_quote(split_cmd[*i][*j], quote);
			if (*quote != 0)
				ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd[*i]) + 1);
			(*j)++;
			(*j) += ft_strccat(out, &split_cmd[*i][*j], SEPARATOR);
			ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd[*i] + 1));
	}
	return (out);
}

#include "stdio.h"

void manage_redirection(t_cmd **cmds, char **split_cmd)
{
	size_t	i;
	size_t	j;
	char	*in;
	char	*out;
	char	quote;
	
	i = 0;
	quote = 0;
	while (split_cmd[i])
	{
		in = malloc(ft_strlen(split_cmd[i]) + 1);
		out = malloc(ft_strlen(split_cmd[i]) + 1);
		in[0] = '\0';
		out[0] = '\0';
		j = 0;
		while (split_cmd[i][j])
		{
			inside_quote(split_cmd[i][j], &quote);
			if (quote == 0)
			{
				in = redirection_in(in, split_cmd, &i, &j, &quote);
				out = redirection_out(out, split_cmd, &i, &j, &quote);
			}
			if (!split_cmd[i][j])
				break;
			j++;
		}
		(*cmds)[i].str_in = remove_quote(in);
		(*cmds)[i++].str_out = remove_quote(out);
	}
}
