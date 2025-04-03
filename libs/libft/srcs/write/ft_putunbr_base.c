/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:11:45 by dernst            #+#    #+#             */
/*   Updated: 2024/12/15 18:18:04 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putunbr_base(unsigned long int n, char *base)
{
	char				*result;
	unsigned long int	nb;
	int					i;
	size_t				len_base;

	len_base = ft_strlen(base);
	i = ft_uintlen_base(n, len_base);
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	result[i] = '\0';
	i--;
	nb = n;
	while (nb > len_base - 1)
	{
		result[i] = base[nb % len_base];
		nb /= len_base;
		i--;
	}
	result[i] = base[nb % len_base];
	return (result);
}
