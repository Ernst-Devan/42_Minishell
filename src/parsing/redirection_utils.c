/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:41:39 by dernst            #+#    #+#             */
/*   Updated: 2025/06/24 15:41:52 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

char	*redirection_in(char *in, char *split_cmd, size_t *j, char *quote)
{
	size_t	len;

	len = ft_strlen(split_cmd);
	if (split_cmd[*j] == '<')
	{
		(*j) += ft_strccat(in, &split_cmd[*j], SEP);
		ft_strlcat(in, SEP2, ft_strlen(split_cmd) + 1);
		inside_quote(split_cmd[*j], quote);
		if (*quote != 0)
			ft_strlcat(in, SEP2, ft_strlen(split_cmd) + 1);
		if (*j < len)
		{
			(*j)++;
			(*j) += ft_strccat(in, &split_cmd[*j], SEP);
		}
		ft_strlcat(in, SEP2, ft_strlen(split_cmd + 1));
	}
	return (in);
}

char	*redirection_out(char *out, char *split_cmd, size_t *j, char *quote)
{
	size_t	len;

	len = ft_strlen(split_cmd);
	if (split_cmd[*j] == '>')
	{
		(*j) += ft_strccat(out, &split_cmd[*j], SEP);
		ft_strlcat(out, SEP2, ft_strlen(split_cmd) + 1);
		inside_quote(split_cmd[*j], quote);
		if (*quote != 0)
			ft_strlcat(out, SEP2, ft_strlen(split_cmd) + 1);
		if (*j < len)
		{
			(*j)++;
			(*j) += ft_strccat(out, &split_cmd[*j], SEP);
		}
		ft_strlcat(out, SEP2, ft_strlen(split_cmd + 1));
	}
	return (out);
}

size_t	check_redirection(char **split_cmd)
{
	size_t	i;
	size_t	count;

	i = 0;
	while (split_cmd[i])
	{
		count = count_chars(split_cmd[i], "><");
		if (count > 0)
			return (1);
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
	{
		free(*in);
		return (1);
	}
	(*out)[0] = '\0';
	return (0);
}
