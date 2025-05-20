/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:13:22 by njooris           #+#    #+#             */
/*   Updated: 2025/05/20 10:04:49 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

int	pwd(t_cmd cmd)
{
	char	*str;

	if (cmd.args[1])
	{
		printf("pwd : too many arguments\n");
		return (1);
	}
	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
