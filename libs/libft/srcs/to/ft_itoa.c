/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:07:42 by dernst            #+#    #+#             */
/*   Updated: 2024/11/27 20:33:55 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	manage_sign(int *sign, long int *num)
{
	if (*num < 0)
	{
		*sign = 1;
		*num *= -1;
	}
}

char	*ft_itoa(int n)
{
	size_t		i;
	int			sign;
	char		*result;
	long int	num;

	num = n;
	sign = 0;
	i = ft_intlen(num);
	manage_sign(&sign, &num);
	result = malloc(sizeof(char) * (i + sign + 1));
	if (!result)
		return (NULL);
	result[i + sign] = '\0';
	i--;
	i += sign;
	while (num > 9)
	{
		result[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	result[i] = (num % 10) + '0';
	if (sign == 1)
		result[0] = '-';
	return (result);
}
