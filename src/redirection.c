// DONT FORGET TO ADD THE HEADER

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>

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

	if (!count_characters(str, "\"\'"))
		return(str);
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

size_t	check_empty(char **lstr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lstr[i])
	{
		while(lstr[i][j])
		{
			if (ft_isascii(lstr[i][j]) && lstr[i][j] != SEPARATOR)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
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
	if (check_empty(split_cmd) == 0)
	{
		free_lstr(split_cmd);
		return (NULL);
	}
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
					if (split_cmd[i][j])
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

// ADDING max for all other category like Path_max Name_max Command_max etc..

char	*redirection_in(char *in, char *split_cmd, size_t *j, char *quote)
{
	size_t	len;

	len = ft_strlen(split_cmd);
		if (split_cmd[*j] == '<')
		{
			(*j) += ft_strccat(in, &split_cmd[*j], SEPARATOR);
			ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd) + 1);
			inside_quote(split_cmd[*j], quote);
			if (*quote != 0)
				ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd) + 1);
			if (*j < len)
			{
				(*j)++;
				(*j) += ft_strccat(in, &split_cmd[*j], SEPARATOR);
			}
			ft_strlcat(in, SEPARATOR2, ft_strlen(split_cmd + 1));
	}
	return (in);
}

char	*redirection_out(char *out, char *split_cmd, size_t *j, char *quote)
{
	size_t	len;

	len = ft_strlen(split_cmd);
	if (split_cmd[*j] == '>')
	{	
		(*j) += ft_strccat(out, &split_cmd[*j], SEPARATOR);
		ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd) + 1);
		inside_quote(split_cmd[*j], quote);
		if (*quote != 0)
			ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd) + 1);
		if (*j < len)
		{
			(*j)++;
			(*j) += ft_strccat(out, &split_cmd[*j], SEPARATOR);
		}
		ft_strlcat(out, SEPARATOR2, ft_strlen(split_cmd + 1));
	}
	return (out);
}


size_t	check_redirection(char **split_cmd)
{
	size_t	i;

	i = 0;
	while (split_cmd[i])
	{
		if (count_characters(split_cmd[i], "><") > 0)
			return(1);
		i++;
	}
	return (0);
}



size_t	init_redirection(char **in, char **out, char *cmd)
{
	*in = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!*in)
		return (1);
	(*in)[0] = '\0';
	*out = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!*out)
		return (1);
	(*out)[0] = '\0';
	return (0);
}

char	**manage_redirection(t_cmd **cmds, char **split_cmd)
{
	size_t	i;
	size_t	j;
	char	*in;
	char	*out;
	char	quote;

	i = 0;	
	quote = 0;
	if (!check_redirection(split_cmd))
		return(split_cmd);
	while (check_empty(split_cmd) == 1 && split_cmd[i])
	{
		init_redirection(&in, &out, split_cmd[i]);
		j = 0;
		while (split_cmd[i][j])
		{
			inside_quote(split_cmd[i][j], &quote);
			if (quote == 0)
			{
				in = redirection_in(in, split_cmd[i], &j, &quote);
				out = redirection_out(out, split_cmd[i], &j, &quote);
			}
			if (!split_cmd[i][j])
				break;
			j++;
		}
		(*cmds)[i].str_in = remove_quote(in);
		(*cmds)[i++].str_out = remove_quote(out);
	}
	return (skip_redirection(split_cmd));
}
