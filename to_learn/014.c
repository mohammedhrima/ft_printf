#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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

int	convertfromDesToHex(unsigned int num, char x)
{
	unsigned int 	len;
	int				i;
	int				j;
	char			*to;

	if(x == 'x')
		to = "0123456789abcdef";
	if(x == 'X')
		to = "0123456789ABCDEF";
	len = (unsigned)ft_strlen(to);
	i = 0;
	j = 0;
	if(num < len)
	{
		j = ft_putchar(to[num]);
		if(j < 0)
			return (-1);
		i += j;
	}
	if(num >= len)
	{
		j = convertfromDesToHex(num/len, x);
		if(j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num%len]);
		if(j < 0)
			return(-1);
		i += j;
	}
	return (i);
}

int convertfromDec_X_U(unsigned int num, char x)
{
	unsigned int len;
	int i;
	int	j;
	char	*to;

	i = 0;
	if(x == 'x')
		to = "0123456789abcdef";
	if(x == 'X')
		to = "0123456789ABCDEF";
	len = (unsigned)ft_strlen(to);
	if(num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if(j < 0)
			return (-1);
		i += j;
	}
	if(num >= len)
	{
		j = convertfromDec_X_U(num/len, x);
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

int convertfromDec_P(unsigned long long num, char x)
{
	long int len;
	int i;
	int	j;
	char *to;

	i = 0;
	if(x == 'x')
		to = "0123456789abcdef";
	if(x == 'X')
		to = "0123456789ABCDEF";
	len = (long)ft_strlen(to);
	if(num >= 0 && num < len)
	{
		j = ft_putchar(to[num]);
		if(j < 0)
			return (-1);
		i += j;
	}
	if(num >= len)
	{
		j = convertfromDec_P(num/len, x);
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

int lenD(long int num)
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

int lenU(unsigned long num)
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

int lenX(unsigned int num, char x)
{
	unsigned int len;
	static char *str;
	char		*to;
	int i;

	
	str = NULL;
	i = 0;
	if(x == 'x')
		to = "0123456789abcdef";
	if(x == 'X')
		to = "0123456789ABCDEF";
	len = (unsigned)ft_strlen(to);
	if(num >= 0 && num < len)
	{
	//	str = join_char_to_str(str, to[num]);
		i++;
	}
	if(num >= len)
	{
		i +=  lenX(num/len, x);
	//	str = join_char_to_str(str,to[num%len]);
		i++;
	}
	return(i);
}

int lenP(unsigned long int num)
{
	unsigned long int len;
	static char *str;
	char  *to;
	int i;
	int	j;

	to = "0123456789abcdef";
	len = (unsigned long int)ft_strlen(to);
	i = 0;
	str = NULL;
	if(num >= 0 && num < len)
		i++;
	if(num >= len)
	{
		i += lenP(num/len);
		i++;
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
	if(s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 's' && s[i] != 'c' && s[i] != 'u')
		return(0);
	return(res);
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

int ft_printf(const char *conv, ...)
{
	int					len;
	int					i;
	int					j;
	int					c;
	char				*s;
	unsigned long long	p;
	int					d;
	unsigned			u;
	unsigned int		x;
	va_list				args;
	int					addOx;
	int					addZero;
	int					addSpaceBefore;
	int					addSpaceAfter;

	len = ft_strlen(conv);
	i = 0;
	j = 0;
	addOx = 0;
	addZero = 0;
	addSpaceAfter = 0;
	addSpaceBefore = 0;
	va_start(args, conv);
	while(i < len)
	{
		if(conv[i] == '%')
		{
			i++;
			if(conv[i] == '-')
			{
				addSpaceAfter = ft_atoi_for_space(conv + i);
				if(addSpaceAfter)
					i += lenD(addSpaceAfter);
				i++;
			}
			if(conv[i] == '+')
			{
				addSpaceBefore = ft_atoi_for_space(conv + i);
				if(addSpaceBefore)
					i += lenD(addSpaceBefore);
				i++;
			}			
			if(conv[i] == '#')
			{
				addOx = 1;
				i++;
			}
			if(conv[i] == '0')
			{
				addZero = ft_atoi_for_addZero(conv + i);
				if(addZero)
					i += lenD(addZero);	
				i++;
			}			
			if(conv[i] == 'c')
			{
				c = va_arg(args,int);
				j += printSpace(&addSpaceBefore, 1);
 				j += ft_putchar(c);
				j += printSpace(&addSpaceAfter, 2);				
			}
			if(conv[i] == 's')
			{
				s = va_arg(args, char *);
				j += printSpace(&addSpaceBefore, ft_strlen(s));
				j += ft_putstr(s);
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'p')
			{
				p = (unsigned long long)va_arg(args, void *);
				j += printSpace(&addSpaceBefore, j + 2 + lenP(p));
				j += ft_putstr("0x") + convertfromDec_P(p,'x');
				j += printSpace(&addSpaceAfter, 2 + lenP(p) + 1); // +1 for \0
			}
			if(conv[i] == 'i' || conv[i] == 'd')
			{
				d = (long int)va_arg(args, int);
				if(addZero)
				{
					addZero -= lenD(d);
					while(addZero--)
						j += ft_putchar('0');
				}
				j += ft_putnbr(d);
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'u')
			{
				u = va_arg(args, unsigned);
				j += printSpace(&addSpaceBefore, j + lenU(u));
				j += ft_putunsignednbr(u);
				j += printSpace(&addSpaceAfter, j);
			}
			if(conv[i] == 'x' || conv[i] == 'X')
			{
				x = (unsigned int)va_arg(args, void*);
				if(addOx && x)
				{
					j += ft_putstr("0");
					j += ft_putchar(conv[i]);
					if(addZero)
						addZero -= 2;
				}
				if(addZero)
				{
					addZero -= lenD(d);
					while(addZero--)
						j += ft_putchar('0');
				}
				j += convertfromDec_X_U(x, conv[i]);
				j += printSpace(&addSpaceAfter, j);
			}
			if (conv[i] == '%')
			{
				j += ft_putchar('%');
				j += printSpace(&addSpaceAfter, j);
			}
			i++;
		}
		else{
			j += ft_putchar(conv[i]);
			i++;
		}
	}
	va_end(args);
	return(j);
}


int main(void)
{
	int x = 123456;
	char *str = "abcdefghi";
	char c = 'x';
	char *ptr = &c;
	//ptr = 0x124456454564;
	unsigned long int m = (unsigned long int)ptr;

	/*printf ("<%25d>\n", x);
	printf("\n");
	ft_printf ("<%25d>\n", x);
	printf("\n");*/
	printf ("<%25s>\n", str);
	printf("\n");
	ft_printf ("<%25s>\n", str);
	printf("\n");
	printf ("<%-25c>\n", c);
	printf("\n");
	ft_printf ("<%-25c>\n", c);
	printf("\n");
	printf ("<%-25u || %-25p>\n", x, ptr);
	printf("\n");
	ft_printf ("<%-25u || %-25p>\n", x, ptr);
	printf("\n");
	printf("<aa%-30p>\n", ptr);
	printf("\n");
	ft_printf("<aa%-30p>\n", ptr);
	printf("\n");
	int number = 15;
	printf("|%-10x|\n", number);  
    ft_printf("|%-10x|\n", number); 
}