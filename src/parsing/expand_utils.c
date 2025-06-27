/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:59:57 by dernst            #+#    #+#             */
/*   Updated: 2025/06/24 17:19:04 by dernst           ###   ########.fr       */
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
	{
		free(variable);
		return (NULL);
	}
	free(variable);
	return (buffer);
}

void	remove_expand_sep(char *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == EXPAND)
		{
			j++;
			continue ;
		}
		if (cmd[i] && cmd[j])
			cmd[i++] = cmd[j++];
	}
	cmd[i] = '\0';
}

void	remove_expand_list(char	**list_cmds)
{
	size_t	i;

	i = 0;
	while (list_cmds[i])
	{
		remove_expand_sep(list_cmds[i]);
		i++;
	}
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
