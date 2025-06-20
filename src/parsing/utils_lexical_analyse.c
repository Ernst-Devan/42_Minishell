/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexical_analyse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:10:46 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 13:18:40 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
