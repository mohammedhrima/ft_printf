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

int	ft_atoi_for_printf(const char *s)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while(s[i] >= '0' && s[i] <= '9')
	{
		res = res *10 +  s[i] - '0';
		i++;
	}
	if(s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X')
		return(0);
	return(res);
}

int lend(long int num)
{
	int i;

	i = 0;
	if(!num)
		return(1);
	while (num > 0)
	{
		num /=10;
		i++;
	}
	return(i);
}

int lenX(unsigned int num)
{
	int i;

	i = 0;
	if(!num)
		return(1);
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return(i);
}

// # is handled


int ft_printf(const char *conv, ...)
{
	int len = ft_strlen(conv);
	int i;
	int j;
	int addOX;
	int addZero;
	unsigned int x;
	long int d;

	j = 0;
	va_list args;
	va_start(args, conv);
	i = 0;
	addOX = 0;
	addZero = 0; 
	while (i < len)
	{
		if (conv[i] == '%')
		{
			i++;
			if(conv[i] == '#')
			{
				addOX = 1;
				i++;
			}
			if(conv[i] == '0')
			{
				//printf("conv -> %s\n", conv + i );
				addZero = ft_atoi_for_printf(conv + i);
				if(addZero)
					i += lend(addZero) + 1;
				else
					i++;
				printf("lqit zero addZero -> %d len -> %d\n", addZero, lend(addZero));
			}
			if (conv[i] == 'c')
				j +=  ft_putchar(va_arg(args, int));
			if (conv[i] == 's')
				j += ft_putstr(va_arg(args, char *));
			if (conv[i] == 'p')
				j += ft_putstr("0x") + convertfromDec_P((unsigned long long)(va_arg(args, void *)), "0123456789abcdef");	
			if(conv[i] == 'x')
			{
				x = (unsigned int)va_arg(args, void*);
				//printf("addZero -> %d\n", addZero);
				printf("x -> %u lenx -> %d addZero -> %d\n", x, lenX(x), addZero);
				if(addOX && x)
				{
					j += ft_putstr("0x");
					if(addZero)
						addZero -= 2;
				}
				if(addZero)
				{
					addZero -= lenX(x);
					while(addZero--)
						j += ft_putchar('0');
				}
				j += convertfromDec_P(x, "0123456789abcdef");
			}
			if(conv[i] == 'X')
			{
				x = (unsigned int)va_arg(args, void*);
				if(addOX && x)
					j += ft_putstr("0X");
				j +=  convertfromDec_P(x, "0123456789ABCDEF");
			}
			if (conv[i] == 'd' || conv[i] == 'i')
			{
				d = (long int)va_arg(args, int);
				if(addZero)
				{
					addZero -= lend(d);
					while(addZero--)
						j += ft_putchar('0');
				}
				j += ft_putnbr(d);
			}
			if(conv[i] == 'u')
				j += ft_putunsignednbr(va_arg(args, unsigned));
			if (conv[i] == '%')
				j += ft_putchar('%');
			i++;
		}
		else
		{	j += ft_putchar(conv[i]);
			i++;
		}
	}
	va_end(args);
	return (j);
}


int main(void)
{
	unsigned int n = 10000;
	printf("%#010x\n",n );
	printf("%#010x\n",0 );
	printf("======================\n");
	ft_printf("%#010x\n", n);
	ft_printf("%#010x\n", 0);
	//printf("======================\n");
//	printf("-> %d\n", lend(124));
}