#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void ft_putchar(int c)
{
	write(1, &c, 4);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(long int num)
{
	if(num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num >= 0 && num < 10)
		ft_putchar('0' + num);
	if (num > 10)
	{
		ft_putnbr(num/10);
		ft_putchar(num%10 + '0');
	}
}

void convertfromDec(long int num, char *to)
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
		ft_putnbr(num/10);
		ft_putchar(num%10 + '0');
	}
}
int ft_printf(const char *conv, ...)
{
	int len = ft_strlen(conv);
	int i;

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
			}
			if (conv[i] == 's')
			{
				char *s = va_arg(args, char *);
				ft_putstr(s);
			}
			if (conv[i] == 'p')
			{
				void *p = va_arg(args, void *);
				ft_putstr("0x");
				convertfromDec((long)p, "0123456789abcdef");
			}
			if(conv[i] == 'x')
			{
				int x = va_arg(args, int);
				ft_putstr("0x");
				convertfromDec((long)x, "0123456789abcdef");
			}
			if(conv[i] == 'X')
			{
				int x = va_arg(args, int);
				ft_putstr("0X");
				convertfromDec((long)x, "0123456789ABCDEF");
			}
			if (conv[i] == 'd' || conv[i] == 'i')
			{
				int d = va_arg(args, int);
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
//	printf("\n");
	return (0);
}

int main(void)
{
	int a = 'a';
	char mychar = 'x';
	char *str = "abcd";
	char *ptr = &mychar;
	unsigned int x = 10;
	//unsigned int ptr1 = (unsigned int)0x454545454;
	//int num = 54945454464;
	// printf("%p -> %d\n",ptr,(int)ptr);
	// printf("0x%lx",(unsigned long*)ptr);
	// write(1, ptr , sizeof(unsigned long*));
	// printf("\n");
	// write(1, ptr,16);
	// ft_printf("a = gg%cggg",a);
	// ft_printf("mychar = %c", mychar);
	// ft_printf("str = %s", str);
	// ft_printf("ptr = %p", ptr);
	ft_printf("%p\n",ptr);
	printf("%p\n",ptr);
	ft_printf("%s\n",ptr);
	printf("%s\n",ptr);
	//printf("%%\n");
	//ft_printf("num = %d", num);
	//ft_printf("ee1455445456456");
}