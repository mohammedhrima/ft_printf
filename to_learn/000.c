/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 02:39:29 by mhrima            #+#    #+#             */
/*   Updated: 2022/11/04 04:23:37 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int ft_putchar(int c)
{
	int i;

	i = (int)write(1, &c, 1);
	return(i);
}

int ft_putstr(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	if(!str)
		return(ft_putstr("(null)"));
	while (i < ft_strlen(str))
	{
		j =  ft_putchar(str[i]);
		if(j < 0)
			return(-1);
		i++;
		k += j;
	}
	return(k);
}

int	ft_putnbr(long int num)
{
	int i;
	int j;

	i = 0;
	if(num < 0)
	{
		j = ft_putchar('-');
		if(j < 0)
			return(-1);
		i += j;
		num = -num;
	}
	if (num >= 0 && num < 10)
	{
		j = ft_putchar('0' + num);
		if (j < 0)
			return(-1);
		i += j;
	}
	if (num >= 10)
	{
		j = ft_putnbr(num/10);
		if(j < 0)
			return(-1);
		i += j;
		j = ft_putchar(num%10 + '0');
		if(j < 0)
			return (-1);
		i += j;
	}
	return(i);
}

int	ft_putunsignednbr(unsigned int num)
{
	int i;
	int j;

	i = 0;
	if (num >= 0 && num < 10)
	{
		j = ft_putchar('0' + num);
		if (j < 0)
			return(-1);
		i += j;
	}
	if (num >= 10)
	{
		j = ft_putunsignednbr(num/10);
		if(j < 0)
			return(-1);
		i += j;
		j = ft_putchar(num%10 + '0');
		if(j < 0)
			return (-1);
		i += j;
	}
	return(i);
}

int convertfromDec_P(unsigned long long num, char *to)
{
	long int len = (long)ft_strlen(to);
	int i;
	int	j;
	i = 0;

	if(num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if(j < 0)
			return (-1);
		i += j;
	}
	if(num >= len)
	{
		j = convertfromDec_P(num/len, to);
		if(j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num%len]);
		if(j < 0)
			return(-1);
		i += j;
	}
	return(i);
}

int convertfromDec_X(unsigned int num, char *to)
{
	unsigned int len = (unsigned)ft_strlen(to);
	int i;
	int	j;
	i = 0;

	if(num < 0)
	{
		num *= -1;
		j = ft_putchar('-');
		i += j;
	}
	if(num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if(j < 0)
			return (-1);
		i += j;
	}
	if(num >= len)
	{
		j = convertfromDec_X(num/len, to);
		if(j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num%len]);
		if(j < 0)
			return(-1);
		i += j;
	}
	return(i);
}

int ft_printf(const char *conv, ...)
{
	int len = ft_strlen(conv);
	int i;
	int j;

	j = 0;
	va_list args;
	va_start(args, conv);
	i = 0;
	while (i < len)
	{
		if (conv[i] == '%')
		{
			i++;
			if (conv[i] == 'c')
				j +=  ft_putchar(va_arg(args, int));
			if (conv[i] == 's')
				j += ft_putstr(va_arg(args, char *));
			if (conv[i] == 'p')
				j += ft_putstr("0x") + convertfromDec_P((unsigned long long)(va_arg(args, void *)), "0123456789abcdef");	
			if(conv[i] == 'x')
				j += convertfromDec_P((unsigned int)va_arg(args, void*), "0123456789abcdef");
			if(conv[i] == 'X')
				j +=  convertfromDec_P((unsigned int)va_arg(args, void*), "0123456789ABCDEF");
			if (conv[i] == 'd' || conv[i] == 'i')
				j += ft_putnbr((long int)va_arg(args, int));
			if(conv[i] == 'u')
				j += ft_putunsignednbr(va_arg(args, unsigned));
			if (conv[i] == '%')
				j += ft_putchar('%');
		}
		else
			j += ft_putchar(conv[i]);
		i++;
	}
	va_end(args);
	return (j);
}
