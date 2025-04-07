/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:17:18 by njooris           #+#    #+#             */
/*   Updated: 2025/04/04 17:32:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "parsing.h"

int	ms_cd(t_command command)
{
	if (chdir(command.args[0]) == -1)
	{
		perror("chdir on ms_cd");
		return (1);
	}
	return (0);
}
