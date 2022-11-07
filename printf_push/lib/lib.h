/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:44:05 by mhrima            #+#    #+#             */
/*   Updated: 2022/11/06 10:44:06 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(char *str, char to_find);
int		ft_atoi(const char *s);
int		print_space(int *addSpace);
int		ft_strlen(const char *str);
int		ft_putchar(int c);
int		ft_putstr(char *str, int n);
int		ft_putnbr(long int num);
int		ft_putunsignednbr(unsigned int num);
int		len_d(long int num);
int		len_x(unsigned int num);
int		len_p(unsigned long long p);
int		len_u(unsigned int num);
int		convert_from_dec_p(unsigned long long num);
int		convert_from_dec_x(unsigned int num, char x);
int		*set_flag(int *flags, char flag, const char *conv, int *i);
int		*set_flag_arr(int *flags, const char *conv, int *i);
void	reset_flag_arr(int *flags);
void	handle_char(int *flags, int c, int *j);
void	handle_string(int *flags, char *s, int *j);
void	handle_pointer(int *flags, unsigned long long *p, int *j);
void	handle_x(int *flags, unsigned int x, int *j, const char conv);
void	handle_number(int *flags, long int d, int *j);
void	handle_unsigned(int *flags, unsigned int u, int *j);
void	handle_percent(int *flags, char m, int *j);
void	get_argument(const char conv, va_list args, int *flags, int *j);
//void	ft_function(int *flags, const char *conv, int *i, int *j, va_list args);

#endif