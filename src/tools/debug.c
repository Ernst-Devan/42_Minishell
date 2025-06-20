/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:08:46 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 15:09:10 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include "stdio.h"

void	display_table(t_table table)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < table.cmd_len)
	{
		printf("\ntype : %zu\n", table.cmds[i].type);
		printf("cmd  : %s\n", table.cmds[i].path);
		printf("args : ");
		if (table.cmds[i].args && !table.cmds[i].args[0])
			printf("(null)");
		while (table.cmds[i].args && table.cmds[i].args[j])
		{
			printf("%s ", table.cmds[i].args[j]);
			j++;
		}
		j = 0;
		printf("\nin : %d\n", table.cmds[i].in);
		printf("out : %d\n", table.cmds[i].out);
		printf("str_in : %s\n", table.cmds[i].str_in);
		printf("str_out : %s\n", table.cmds[i].str_out);
		i++;
	}
	printf("\n");
}

void	display_lstr(char **lstr)
{
	size_t	i;

	i = 0;
	if (!lstr[i])
		printf(" (null)\n");
	while (lstr[i])
	{
		printf("%s\n", lstr[i]);
		i++;
	}
	printf("\n");
}
