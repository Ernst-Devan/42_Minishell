/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexical_analyse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:10:46 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 13:11:57 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

size_t	quote_check(char *input)
{
	char	quote;
	size_t	j;

	j = 0;
	quote = 0;
	while (input[j])
	{
		inside_quote(input[j], &quote);
		j++;
	}
	if (quote)
		return (2);
	return (0);
}
