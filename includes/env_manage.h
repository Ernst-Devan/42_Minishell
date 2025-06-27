/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:16:29 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 15:16:30 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGE_H 
# define ENV_MANAGE_H

# include "parsing.h"

char	**new_env(char **env);
int		size_of_env(char **env);
void	print_env(char **env);

#endif
