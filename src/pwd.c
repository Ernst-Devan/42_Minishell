/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:13:22 by njooris           #+#    #+#             */
/*   Updated: 2025/05/07 13:51:24 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "parsing.h"
#include "exec.h"
#include "libft.h"

int	pwd(char **env)
{
	int	i;
	
	i = find_env_variable(env, "PWD=");
	if (i == -1)
		return (1);
	printf("%s\n", &env[i][4]);
	return (0);
}
