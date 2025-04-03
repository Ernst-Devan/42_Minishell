/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:26:57 by dernst            #+#    #+#             */
/*   Updated: 2025/04/03 11:34:13 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_word(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0' || line[i] == '\n')
	{
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		while (line[i] > 32 && line[i] != '\0')
			i++;
		if (line[i - 1] > 32)
			count++;
		i++;
	}
	return (count);
}