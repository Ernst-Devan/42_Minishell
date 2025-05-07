/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:10:42 by dernst            #+#    #+#             */
/*   Updated: 2025/04/28 16:19:27 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>
Quotes:

Quotes not closes : Return error inside the terminal same if the closes quotes is inside a expand
Single quotes : Prevent the expand -> Modify the adding expand inside the list of variable


Delete all the space from the input except for the contain of quotes
Delete the useless quotes like "" '' to resume -> skip quotes open/close

QUOTES WORKS WITH A SYSTEM OF MAIN QUOTES


void	manage_quotes()
{
	size_t	count_d;
	size_t	count_s;
	char	main_quotes = ' or "

	count_d = 0;
	count_s = 0;

	while (input)
		check_simple -> count_s ++;
		check_double -> count_d ++

	

	if (count_s % 2 || count_d %2 == 1)
	 message d'erreur 
}

Think the case with the heredock and the expend inside it
Make a strjoin custom to detect the case "|" cause change the number of command in the struct table
Good idea to just check the current quotes open
Return the good error code if the quotes isn't close

void	check_simple()
{
	char *temp;


	return (the contents of the quotes)
}


