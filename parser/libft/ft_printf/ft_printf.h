/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 13:03:30 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/05 12:11:03 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(char const *s, ...);
int	ft_printf_err(char const *s, ...);
int	ft_printf_fd(int fd, char const *s, ...);

int	eval_insert(int fd, char c, va_list args);
int	write_loop(int fd, char const *s, va_list args);

int	printf_write_char(int fd, char c);
int	printf_write_str(int fd, char const *s);

int	printf_write_ptr(int fd, void *p);
int	printf_write_nbr(int fd, int n);
int	printf_write_nbr_unsigned(int fd, unsigned int n);
int	printf_write_hex(int fd, unsigned int n, int caps);

#endif