#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
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
	return (i);
}

int ft_putstr(char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (i < ft_strlen(str))
	{
		j = ft_putchar(str[i]);
		if (j < 0)
			return (-1);
		i++;
		k += j;
	}
	return (k);
}

int ft_putnbr(long int num)
{
	int i;
	int j;

	i = 0;
	if (num < 0)
	{
		j = ft_putchar('-');
		if (j < 0)
			return (-1);
		i += j;
		num = -num;
	}
	if (num >= 0 && num < 10)
	{
		j = ft_putchar('0' + num);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= 10)
	{
		j = ft_putnbr(num / 10);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(num % 10 + '0');
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int ft_putunsignednbr(unsigned int num)
{
	int i;
	int j;

	i = 0;
	if (num >= 0 && num < 10)
	{
		j = ft_putchar('0' + num);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= 10)
	{
		j = ft_putunsignednbr(num / 10);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(num % 10 + '0');
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int convertfromDec_P(unsigned long long num, char *to)
{
	unsigned long long len = (unsigned long long)ft_strlen(to);
	int i;
	int j;
	i = 0;

	if (num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= len)
	{
		j = convertfromDec_P(num / len, to);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num % len]);
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int convertfromDec_X(unsigned int num, char *to)
{
	unsigned int len = (unsigned)ft_strlen(to);
	int i;
	int j;
	i = 0;

	if (num < 0)
	{
		num *= -1;
		j = ft_putchar('-');
		i += j;
	}
	if (num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= len)
	{
		j = convertfromDec_X(num / len, to);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num % len]);
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int ft_atoi_for_addZero(const char *s)
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
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + s[i] - '0';
		i++;
	}
	if (s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X' && s[i] != 's' && s[i] != 'u')
		return (0);
	return (neg * res);
}
int ft_atoi_for_space(const char *s)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + s[i] - '0';
		i++;
	}
	if (s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 's' && s[i] != 'c' && s[i] != 'u')
		return (0);
	// printff("-> %d\n", res);
	return (res);
}

int ft_atoi_for_precision(const char *s)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + s[i] - '0';
		i++;
	}
	return (res);
}

int lend(long int num) // doesn't count the minus sign
{
	int i;

	i = 0;
	if (!num)
		return (1);
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int lenU(unsigned num)
{
	int i;

	i = 0;
	if (!num)
		return (1);
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int lenX(unsigned int num, char *to)
{
	unsigned int len = (unsigned)ft_strlen(to);
	int i;
	int j;
	i = 0;

	if (num >= 0 && num < len)
		i++;
	if (num >= len)
	{
		j = lenX(num / len, to);
		i += j;
		i++;
	}
	return (i);
}

int lenP(unsigned long long p, char *to)
{
	unsigned long long len = (unsigned long long)ft_strlen(to);
	int i;
	int j;
	i = 0;

	if (p >= 0 && p < len)
		i++;
	if (p >= len)
	{
		j = lenP(p / len, to);
		i += j;
		i++;
	}
	return (i);
}

int printSpace(int *addSpace, int len)
{
	int i;

	i = 0;
	*addSpace -= len;
	while ((*addSpace)-- > 0)
	{
		i += ft_putchar(' ');
	}
	return (i);
}

size_t ft_strncpy(char *dst, char *src, size_t size)
{
	unsigned int j;

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

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *ptr;
	unsigned int i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft_strdup(const char *s)
{
	char *ptr;
	int i;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	unsigned int	j;

	j = 0;
	if (!size)
		return (ft_strlen(src));
	while (j < size - 1 && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(src));
}


/*void printfString(char *s, int **precision, int *j, int *addSpaceAfter)
{
	//char *src;
	int i;

	i = 0;
	if (!s)
	{
		printfString("(null)", precision, j, addSpaceAfter);
		return;
	}
	//src = ft_strdup(s);
	if ((*precision)[0])
	{
		//src =(char*)malloc(ft_strlen(s) + 1);
		while((*precision)[1]-- > 0)
			*j += ft_putchar(s[i++]);
		*j += printSpace(addSpaceAfter, i);
			
		s = //ft_strlcpy(src,s, (*precision)[1] + 1 );
		//src =ft_substr(s, 0, *precision) ;
		//free(s);
		//s = src;
		(*precision)[0] = 0;
		(*precision)[1] = 0;
	}
	else{
		*j += ft_putstr(s);
		*j += printSpace(addSpaceAfter, ft_strlen(s));
	}
	//free(s);
	
}*/

void printString(char *s, int *precision, int *j, int *addSpaceAfter)
{
	int i;

	i = 0;
	if(!s)
	{
		printString("(null)", precision, j, addSpaceAfter);
		return;
	}
	if(*precision >= 0)
	{
		while ((*precision)-- > 0 && *s)
		{	
			j += ft_putchar(*(s++));
			i++;
		}
		j += printSpace(addSpaceAfter, i);
		*precision = 0;
	}
	else{
		*j += ft_putstr(s);
		*j += printSpace(addSpaceAfter, ft_strlen(s));
	}
	
}

int ft_printf(const char *conv, ...)
{
	int len;
	int i;
	int j;
	int addOX;
	int addZero;
	int addSpaceAfter;
	int cutoutput;
	unsigned int x;
	long int d;
	int c;
	char *s;
	unsigned u;
	char *src;
	int addPlus;
	int space_to_skip;
	int precision;

	j = 0;
	va_list args;
	va_start(args, conv);
	i = 0;
	addOX = 0;
	addZero = 0;
	addSpaceAfter = 0;
	cutoutput = 0;
	addPlus = 0;
	len = ft_strlen(conv);
	precision = -1;

	while (i < len)
	{
		if (conv[i] == '%')
		{
			i++;
			space_to_skip = 0;
			addPlus = 0;
			precision = -1;
			while (conv[i] == ' ')
			{
				space_to_skip++;
				i++;
			}
			if (space_to_skip && conv[i] != '+')
				j += ft_putchar(' ');

			if (conv[i] == '0')
			{
				while (conv[i] == '0')
					i++;
				addZero = ft_atoi_for_addZero(conv + i);
				if (addZero)
					i += lend(addZero);
			}
			if (conv[i] == '-')
			{
				addZero = 0;
				while (conv[i] == '-')
					i++;
				addSpaceAfter = ft_atoi_for_space(conv + i);
				if (addSpaceAfter)
					i += lend(addSpaceAfter);
				while (conv[i] == '0')
					i++;
			}
			if (conv[i] == '+')
			{
				addPlus = 1;
				while (conv[i] == '+')
					i++;
				while (conv[i] == ' ')
					i++;
			}
			if (conv[i] == '#')
			{
				addOX = 1;
				i++;
			}
			if (conv[i] == '.') // add space in case there is number after dot
			{
				i++;
				precision = ft_atoi_for_precision(conv + i);
				if(conv[i] >= '0' && conv[i] <= '9' )
					i += lend(precision);
			}

			if (conv[i] == 'c')
			{
				c = va_arg(args, int);
				j += ft_putchar(c);
				j += printSpace(&addSpaceAfter, 1);
			}
			if (conv[i] == 's')
			{
				s = va_arg(args, char *);
			//	printf("\nprecision->%d\n",precision);
				printString(s, &precision, &j,  &addSpaceAfter);
			}
			if (conv[i] == 'p')
			{
				unsigned long long p = (unsigned long long)va_arg(args, void *);
				j += ft_putstr("0x") + convertfromDec_P(p, "0123456789abcdef");
				j += printSpace(&addSpaceAfter, lenP(p, "0123456789abcdef") + 2);
			}
			if (conv[i] == 'x')
			{
				x = (unsigned int)va_arg(args, void *);
				if (addOX && x)
				{
					j += ft_putstr("0x");
					if (addZero)
						addZero -= 2;
				}
				if (addZero)
				{
					addZero -= lenX(x, "0123456789abcdef"); // we should add the len of hexadecimal number
					while (addZero-- > 0)
						j += ft_putchar('0');
				}
				j += convertfromDec_X(x, "0123456789abcdef");
				j += printSpace(&addSpaceAfter, lenX(x, "0123456789abcdef"));
			}
			if (conv[i] == 'X')
			{
				x = (unsigned int)va_arg(args, void *);
				if (addOX && x)
				{
					j += ft_putstr("0X");
					if (addZero)
						addZero -= 2;
				}
				if (addZero)
				{
					addZero -= lenX(x, "0123456789ABCDEF"); // we should add the len of hexadecimal number
					while (addZero-- > 0)
						j += ft_putchar('0');
				}
				j += convertfromDec_X(x, "0123456789ABCDEF");
				j += printSpace(&addSpaceAfter, lenX(x, "0123456789ABCDEF"));
			}
			if (conv[i] == 'd' || conv[i] == 'i')
			{
				d = (long int)va_arg(args, int);
				if (addPlus && d >= 0)
					j += ft_putchar('+');
				if(precision >= 0)
				{
					if (d < 0)
					{
						j += ft_putchar('-');
						d = -d;
						precision++;
					}
					precision = precision - lend(d) - addPlus;
					while(precision-- >= lend(d))
						j += ft_putchar('0');
					precision = -1;
				}
				if (addZero)
				{
					if (d < 0)
					{
						j += ft_putchar('-');
						d = -d;
						addZero--;
					}
					addZero = addZero - lend(d) - addPlus;
					while (addZero-- > 0)
						j += ft_putchar('0');
				}
				j += ft_putnbr(d);
				j += printSpace(&addSpaceAfter, lend(d) + addPlus);
			}
			if (conv[i] == 'u')
			{
				u = va_arg(args, unsigned);
				if (addPlus && d >= 0)
					j += ft_putchar('+');
				if (addZero)
				{
					addZero = addZero - lenU(u) - addPlus;
					while (addZero-- > 0)
						j += ft_putchar('0');
				}
				j += ft_putunsignednbr(u);
				j += printSpace(&addSpaceAfter, lenU(u) + addPlus);
			}
			if (conv[i] == '%')
			{
				j += ft_putchar('%');
				j += printSpace(&addSpaceAfter, j);
			}
			i++;
			//	i -= space_to_skip;
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