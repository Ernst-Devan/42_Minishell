/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:53:24 by dernst            #+#    #+#             */
/*   Updated: 2025/01/30 22:22:19 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"
#include "errno.h"

const char	*start_manage(const char *nptr, t_limits *limits)
{
	const char	*s;
	int			c;

	limits->neg = 0;
	s = nptr;
	c = s[0];
	while (ft_isspace(c))
		c = *s++;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			limits->neg = 1;
		c = *s++;
	}
	limits->coff = LONG_MAX;
	if (limits->neg)
		limits->coff = -(unsigned long)LONG_MIN;
	if (limits->base == 16 && c == '0' && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
	}
	limits->clim = limits->coff % (unsigned long)limits->base;
	limits->coff /= (unsigned long)limits->base;
	return (s);
}

void	atoi_part(char *nptr, t_limits lim, size_t *ac, int *any)
{
	lim.c = nptr[-1];
	while (lim.c)
	{
		if (ft_isdigit(lim.c))
			lim.c -= '0';
		else if (ft_isalpha(lim.c))
		{
			if (ft_isupper(lim.c))
				lim.c -= 'A' - 10;
			else
				lim.c -= 'a' - 10;
		}
		else
			break ;
		if (lim.c >= lim.base)
			break ;
		if (*any < 0 || *ac > lim.coff || (*ac == lim.coff && lim.c > lim.clim))
			*any = -1;
		else
		{
			*any = 1;
			*ac = *ac * lim.base + lim.c;
		}
		lim.c = *nptr++;
	}
}

void	manage_pointer(char **endptr, const char *nptr, int any)
{
	if (endptr != 0)
	{
		if (any)
			*endptr = (char *) nptr - 1;
		else
			*endptr = (char *)nptr;
	}
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	t_limits		limits;
	const char		*s;
	size_t			acc;
	int				c;
	int				any;

	limits.base = base;
	s = start_manage(nptr, &limits);
	c = s[-1];
	acc = 0;
	any = 0;
	atoi_part((char *)s, limits, &acc, &any);
	if (any < 0)
	{
		if (limits.neg)
			acc = LONG_MIN;
		else
			acc = LONG_MAX;
	}
	else if (limits.neg)
		acc = -acc;
	manage_pointer(endptr, nptr, any);
	return (acc);
}
