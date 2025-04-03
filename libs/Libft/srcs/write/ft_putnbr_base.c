/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:28:16 by dernst            #+#    #+#             */
/*   Updated: 2024/11/27 20:35:13 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putnbr_base(int n, char *base)
{
	char		*result;
	long int	nb;
	int			i;
	size_t		len_base;

	i = ft_intlen_base(n, 16);
	len_base = ft_strlen(base);
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	result[i] = '\0';
	i--;
	nb = n;
	while (nb > (long int)len_base)
	{
		result[i] = base[nb % len_base];
		nb /= len_base;
		i--;
	}
	result[i] = base[nb % len_base];
	return (result);
}
