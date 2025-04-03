/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:15 by dernst            #+#    #+#             */
/*   Updated: 2024/12/15 18:16:43 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <libft.h>

size_t	ft_putchar_fd_printf(char c, int fd);
size_t	ft_putnbr_fd_printf(int n, int fd, size_t *len);
size_t	ft_putstr_fd_printf(char *s, int fd);
int		ft_printf(const char *format, ...);
void	check_pourcent(char c, va_list args, size_t *temp_len);

#endif