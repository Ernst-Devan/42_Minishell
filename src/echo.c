/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:02:38 by njooris           #+#    #+#             */
/*   Updated: 2025/04/28 15:46:35 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"


int	echo(t_cmd command)
{
	if (ft_strncmp("-n", command.args[1], 3) == 0)
	{
		if (command.args[2])
			printf("%s", command.args[2]);
	}
	else
		printf("%s\n", command.args[1]);
	return (0);
}



