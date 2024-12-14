/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:52:34 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:52:35 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "unistd.h"
# include "stdarg.h"

int	ft_printf(const char *format, ...);
int	ft_printf_router(va_list *args, char op);
int	ft_putchar_c(int c);
int	ft_putstr_c(char *str);
int	ft_putnbr_c(long n);
int	ft_puthex_c(unsigned int n, char op);
int	ft_putaddr_c(void *addr);
int	ft_putaddr_hex_c(void *addr);

#endif
