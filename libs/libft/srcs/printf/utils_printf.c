/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:06:26 by dernst            #+#    #+#             */
/*   Updated: 2025/01/30 22:22:34 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	ft_putnbr_fd_printf(int n, int fd, size_t *len)
{
	char		current;
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
		*len += 1;
	}
	if (nb > 9)
	{
		current = (nb % 10) + '0';
		ft_putnbr_fd_printf(nb / 10, fd, len);
		write(fd, &current, 1);
		*len += 1;
	}
	else
	{
		*len += 1;
		current = nb + '0';
		write(fd, &current, 1);
	}
	return (*len);
}

size_t	ft_putstr_fd_printf(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}

size_t	ft_putchar_fd_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
