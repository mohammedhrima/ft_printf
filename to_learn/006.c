//#include "libftprintf.h"
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

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
	write(1, &c, 4);
	return(1);
}

int ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return(i);
}

int	ft_putnbr(long int num)
{
	int i;

	i = 0;
	if(num < 0)
	{
		i = ft_putchar('-');
		num = -num;
	}
	if (num >= 0 && num < 10)
		return(ft_putchar('0' + num) + i);
	if (num > 10)
		return(ft_putnbr(num/10) + ft_putchar(num%10 + '0'));
	return(i);
}

void convertfromDec(unsigned int num, char *to)
{
	long int len = (long)ft_strlen(to);
	if(num < 0)
	{
		num *= -1;
		ft_putchar('-');
	}
	if(num)
	{
		convertfromDec(num/len, to);
		ft_putchar(to[num%len]);
	}
}

void	ft_putunsignednbr(unsigned int num)
{
	if (num >= 0 && num < 10)
		ft_putchar('0' + num);
	if (num > 10)
	{
		ft_putunsignednbr(num/10);
		ft_putchar(num%10 + '0');
	}
}

//##############################################//
//printf return how many charaterts it did write//
//if str = NULL -> print (null)					//
//##############################################//

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
			{
				int c = va_arg(args, int);
				ft_putchar(c);
				j++;
			}
			if (conv[i] == 's')
			{
				if((char*)args == NULL)
					printf("is Null\n");
				//printf("%s\n", (char*)args);
				/*char *s = va_arg(args, char *);
				ft_putstr(s);
				j += ft_strlen(s);*/
			}
			if (conv[i] == 'p')
			{
				void *p = va_arg(args, void *);
				ft_putstr("0x");
				convertfromDec((long)p, "0123456789abcdef");
				
			}
			if(conv[i] == 'x')
			{
				int x = va_arg(args, unsigned int);
				ft_putstr("0x"); // add 2 to j
				convertfromDec(x, "0123456789abcdef");
			}
			if(conv[i] == 'X')
			{
				int x = va_arg(args, unsigned int);
				ft_putstr("0X"); // add 2 to j
				convertfromDec(x, "0123456789ABCDEF");
			}
			if (conv[i] == 'd' || conv[i] == 'i')
			{
				long int d = va_arg(args,long int);
				ft_putnbr(d);
			}
			if(conv[i] == 'u')
			{
				unsigned u = va_arg(args, unsigned);
				ft_putunsignednbr(u);
			}
			if (conv[i] == '%')
				ft_putchar('%');
		}
		else
		{
			ft_putchar(conv[i]);
		}
		i++;
	}
	va_end(args);
	return (0);
}

int main(void)
{
	//int n = 123456789;
	//ft_printf("%d\n",n);
	//int r = ft_putnbr(n);
//	printf("\x01\x02\a\v\b\f\r\n");
	//printf("%s", (char *)NULL);
	ft_printf("%s", (char *)NULL);

	
	//printf("%d\n", n);
}