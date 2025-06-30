/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:13:22 by njooris           #+#    #+#             */
/*   Updated: 2025/06/30 16:32:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "exec.h"
#include "libft.h"

int	pwd(t_cmd cmd)
{
	char	*str;

	(void)cmd;
	str = getcwd(NULL, 0);
	if (!str)
	{
		perror("getcwd error");
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
