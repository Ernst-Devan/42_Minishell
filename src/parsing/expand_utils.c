/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:59:57 by dernst            #+#    #+#             */
/*   Updated: 2025/06/24 15:30:43 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
char	*define_expand(char *variable)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!variable)
		return (NULL);
	buffer = ft_calloc(ft_strlen(variable) + 3, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[j++] = EXPAND;
	while (variable[i])
	{
		buffer[j] = variable[i];
		j++;
		i++;
	}
	buffer[j++] = EXPAND;
	buffer[j] = '\0';
	return (buffer);
}

char	*replace_var(char *str, char **env)
{
	char	*variable;
	char	*buffer;

	variable = find_env(str, env);
	if (ft_strlen(variable) == 0)
		return (NULL);
	variable = define_expand(variable);
	if (!variable)
		return (NULL);
	buffer = ft_strdup(variable);
	if (!buffer)
		return (NULL);
	free(variable);
	return (buffer);
}

char	*remove_expand_sep(char *cmd)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	if (!cmd)
		return (cmd);
	buffer = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == EXPAND)
			i++;
		if (cmd[i])
			buffer[j++] = cmd[i++];
	}
	buffer[j] = '\0';
	free(cmd);
	return (buffer);
}

char	**remove_expand_list(char	**list_cmds)
{
	char	**buffer;
	size_t	i;

	buffer = ft_calloc(count_lstr(list_cmds) + 1, sizeof(char *));
	if (!buffer)
		return (NULL);
	i = 0;
	while (list_cmds[i])
	{
		buffer[i] = remove_expand_sep(list_cmds[i]);
		i++;
	}
	buffer[i] = NULL;
	free(list_cmds);
	return (buffer);
}

size_t	count_expand(char *s, size_t *i, size_t *j, char *cs)
{
	size_t	count;

	count = 0;
	while (cs[*j])
	{
		if (s[*i] == EXPAND)
		{
			*i += 1;
			while (s[*i] && s[*i] != EXPAND)
				*i += 1;
			if (!s[*i])
				return (count);
		}
		if (s[*i] == cs[*j])
			count++;
		if (s[*i] == EXPAND)
			break ;
		*j += 1;
	}
	*j = 0;
	*i += 1;
	return (count);
}
