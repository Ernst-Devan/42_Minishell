/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:51:56 by dernst            #+#    #+#             */
/*   Updated: 2024/11/14 14:14:18 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nodes;

	nodes = malloc(sizeof(t_list));
	if (!nodes)
		return (NULL);
	nodes->content = content;
	nodes->next = NULL;
	return (nodes);
}
