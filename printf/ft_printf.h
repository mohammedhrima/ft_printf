/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:11:22 by mhrima            #+#    #+#             */
/*   Updated: 2022/10/31 02:42:30 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
int ft_strlen(const char *str);
int ft_putchar(int c);
int ft_putstr(char *str);
int	ft_putnbr(long int num);
int	ft_putunsignednbr(unsigned int num);
int convertfromDec_P(unsigned long long num, char *to);
int convertfromDec_X(unsigned int num, char *to);
int ft_printf(const char *conv, ...);

#endif