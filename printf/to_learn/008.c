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
	int i;

	i = (int)write(1, &c, 1);
	return(i);
}

int ft_putstr(char *str)
{
	int i;
	int j;

	i = 0;

	while (str[i])
	{
		j =  ft_putchar(str[i]);
		if(j < 0)
			return(-1);
		i += j;
	}
	return(i);
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

int convertfromDec_P(long num, char *to)
{
	long int len = (long)ft_strlen(to);
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
				j +=  ft_putchar(va_arg(args, int));
			if (conv[i] == 's')
			{
				if(va_arg(args, char *) == NULL)
					j += ft_putstr("(null)");
				else if(!ft_strlen(va_arg(args, char *)))
					j += ft_putstr("");
				else
					j += ft_putstr(va_arg(args, char *));
			}
			if (conv[i] == 'p')
				j += ft_putstr("0x") + convertfromDec_P((long)(va_arg(args, void *)), "0123456789abcdef");	
			if(conv[i] == 'x')
				j += convertfromDec_P((unsigned int)va_arg(args, void*), "0123456789abcdef");
			if(conv[i] == 'X')
				j +=  convertfromDec_P((unsigned int)va_arg(args, void*), "0123456789ABCDEF");
			if (conv[i] == 'd' || conv[i] == 'i')
				j += ft_putnbr(va_arg(args,long int));
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

int main(void)
{
	ft_printf("%s", "");
//	ft_printf("%s", (char *)NULL);
//	ft_printf("%s", "some string with %s hehe");
//	ft_printf(" %s", "can it handle \t and \n?");
//	ft_printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
//	ft_printf("%s%s%s", "And ", "some", "joined");
//	ft_printf("%ss%ss%ss", "And ", "some other", "joined");
}