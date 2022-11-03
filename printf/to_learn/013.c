#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

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

int	ft_atoi_for_addZero(const char *s)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while(s[i] >= '0' && s[i] <= '9')
	{
		res = 10*res +  s[i] - '0';
		i++;
	}
	if(s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X')
		return(0);
	return(res);
}

int ft_atoi_for_space(const char *s)
{
	int i;
	int res;
	int neg;

	i = 0;
	res = 0;
	neg = 1;
	while (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while(s[i] >= '0' && s[i] <= '9')
	{
		res = 10*res + s[i] - '0';
		i++;
	}
	if(s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 's' && s[i] != 'c')
		return(0);
	return(res);
}

char	*join_char_to_str(char *s, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	i++;
	free(s);
	str[i] = '\0';
	return (str);
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

int lenX(unsigned int num, char  *to)
{
	unsigned int len = (unsigned)ft_strlen(to);
	static char *str;
	int i;
	int	j;
	i = 0;
	str = NULL;

	if(num < 0)
	{
		num *= -1;
		str = join_char_to_str(str, '-');
		i++;
	}
	if(num >= 0 && num < len)
	{
		str = join_char_to_str(str, to[num]);
		i++;
	}
	if(num >= len)
	{
		j = lenX(num/len, to);
		i += j;
		str = join_char_to_str(str,to[num%len]);
		i++;
	}
	return(i);
}

int printSpace(int *addSpaceAfter, int len)
{
	int i;

	i = 0;
	*addSpaceAfter -= len;
	while((*addSpaceAfter)-- >= 0)
		i += ft_putchar(' ');
	return(i);
}

size_t	ft_strncpy(char *dst, char *src, size_t size)
{
	unsigned int	j;

	j = 0;
	if (!size)
		return (ft_strlen(src));
	while (j < size && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}

// # is handled
int ft_printf(const char *conv, ...)
{
	int len = ft_strlen(conv);
	int i;
	int j;
	int addOX;
	int addZero;
	int addSpaceAfter;
	int addSpaceBefore;
	int cutoutput;
	unsigned int x;
	long int d;
	int c;
	char *s;

	j = 0;
	va_list args;
	va_start(args, conv);
	i = 0;
	addOX = 0;
	addZero = 0;
	addSpaceAfter = 0;
	cutoutput = 0;
	addSpaceBefore = 0;

	while (i < len)
	{
		if (conv[i] == '%')
		{
			i++;
			if(conv[i] == '-')
			{
				addSpaceAfter = ft_atoi_for_space(conv + i);
				if(addSpaceAfter)
					i += lend(addSpaceAfter);
				i++;
			}
			if(conv[i] == '+')
			{
				addSpaceBefore = ft_atoi_for_space(conv + i);
				if(addSpaceBefore)
					i += lend(addSpaceBefore);
				i++;
			}
			if(conv[i] == '#')
			{
				addOX = 1;
				i++;
			}
			if(conv[i] == '.') //add space in case there is number after dot
			{
			//	cutoutput = ft_at
			}
			if(conv[i] == '0')
			{
				addZero = ft_atoi_for_addZero(conv + i);
				if(addZero)
					i += lend(addZero);	
				i++;
			}
			if (conv[i] == 'c')
			{
				c = va_arg(args, int);
				j += printSpace(&addSpaceBefore, 1);
 				j += ft_putchar(c);
				j += printSpace(&addSpaceAfter, j);
			}
			if (conv[i] == 's')
			{
				s = va_arg(args, char *);
				j += printSpace(&addSpaceBefore, ft_strlen(s));
				j += ft_putstr(s);
				j += printSpace(&addSpaceAfter, j);
			}
			if (conv[i] == 'p')
			{
				unsigned long long p = (unsigned long long)va_arg(args, void *);
				j += ft_putstr("0x") + convertfromDec_P(p, "0123456789abcdef");	
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'x')
			{
				x = (unsigned int)va_arg(args, void*);
				if(addOX && x)
				{
					j += ft_putstr("0x");
					if(addZero)
						addZero -= 2;
				}
				if(addZero)
				{
					addZero -= lenX(x,"0123456789abcdef"); //we should add the len of hexadecimal number
					while(addZero--)
						j += ft_putchar('0');
				}
				j += convertfromDec_P(x, "0123456789abcdef");
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'X')
			{
				x = (unsigned int)va_arg(args, void*);
				if(addOX && x)
					j += ft_putstr("0X");
				j +=  convertfromDec_P(x, "0123456789ABCDEF");
				j += printSpace(&addSpaceAfter, j);
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
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'u')
			{
				j += ft_putunsignednbr(va_arg(args, unsigned));
				j += printSpace(&addSpaceAfter, j);
			}
			if (conv[i] == '%')
			{
				j += ft_putchar('%');
				j += printSpace(&addSpaceAfter, j);
			}
			i++;
		}
		else
		{	
			j += ft_putchar(conv[i]);
			i++;
		}
	}
	va_end(args);
	return (j);
}


int main(void)
{
	int x = 123456;
	char *str = "abcdefghi";
	char c = 'x';
	char *ptr = &c;

	/*printf ("<%-25d>\n", x);
	ft_printf ("<%-25d>\n", x);
	printf ("<%-25s>\n", str);
	ft_printf ("<%-25s>\n", str);
	printf ("<%-25c>\n", c);
	ft_printf ("<%-25c>\n", c);
	printf ("<%-25p>\n", ptr);
	ft_printf ("<%-25p>\n", ptr);*/
//	printf ("<%-25d>\n", x);
//	ft_printf ("<%-25d>\n", x);
	//ft_printf("ab%.cd");
	// printf ("<%-25d>\n", b);
	// printf ("<%-25d>\n", c);
	// printf ("<%-25d>\n", d);
	// printf ("<%-25d>\n", e);
	//printf("%20.1s|\n", str);
	printf("-> %i\n", 012);
	printf("-> %d\n",012);
	ft_printf("-> %i\n", 012);
	ft_printf("-> %d\n",012);
}