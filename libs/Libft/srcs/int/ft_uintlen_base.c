/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:09:18 by dernst            #+#    #+#             */
/*   Updated: 2024/12/05 21:20:44 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_uintlen_base(unsigned long int n, size_t base)
{
	size_t	i;

	i = 0;
	while (n > (unsigned long int)base - 1)
	{
		n /= base;
		i++;
	}
	return (++i);
}
