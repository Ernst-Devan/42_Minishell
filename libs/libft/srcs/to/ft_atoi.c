/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:31:24 by ernstdevan        #+#    #+#             */
/*   Updated: 2025/01/30 22:22:44 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_overflow(long n, int sign)
{
	if (n * 10 / 10 != n)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (2);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
		if (check_overflow(result, sign) == -1
			|| check_overflow(result, sign) == 0)
			return (check_overflow(result, sign));
	}
	return (result * sign);
}
