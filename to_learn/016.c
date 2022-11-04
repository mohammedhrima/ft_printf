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
	long int len = (long)ft_strlen(to);
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

	i = 0;
	res = 0;
/*	if(s[i] == '-')
		return (0);*/
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + s[i] - '0';
		i++;
	}
	if (s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X')
		return (0);
	return (res);
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
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + s[i] - '0';
		i++;
	}
	if (s[i] != 'd' && s[i] != 'i' && s[i] != 'x' && s[i] != 'X' && s[i] != 'p' && s[i] != 's' && s[i] != 'c')
		return (0);
	return (res);
}

char *join_char_to_str(char *s, char c)
{
	char *str;
	int i;
	int j;

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

int lend(long int num) //doesn't count the minus sign
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
	static char *str;
	int i;
	int j;
	i = 0;
	str = NULL;

	if (num >= 0 && num < len)
	{
		str = join_char_to_str(str, to[num]);
		i++;
	}
	if (num >= len)
	{
		j = lenX(num / len, to);
		i += j;
		str = join_char_to_str(str, to[num % len]);
		i++;
	}
	return (i);
}

int lenP(unsigned long long p,  char *to)
{
	unsigned long long len = (unsigned long long)ft_strlen(to);
	static char *str;
	int i;
	int j;
	i = 0;
	str = NULL;

	if (p >= 0 && p < len)
	{
		str = join_char_to_str(str, to[p]);
		i++;
	}
	if (p >= len)
	{
		j = lenX(p / len, to);
		i += j;
		str = join_char_to_str(str, to[p % len]);
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

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

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

// # is handled
int ft_printf(const char *conv, ...)
{
	int len = ft_strlen(conv);
	int i;
	int j;
	int addOX;
	int addZero;
	int addSpaceAfter;
	//int addSpaceBefore;
	int cutoutput;
	unsigned int x;
	long int d;
	int c;
	char *s;
	int addPlus;
	int space_to_skip;

	j = 0;
	va_list args;
	va_start(args, conv);
	i = 0;
	addOX = 0;
	addZero = 0;
	addSpaceAfter = 0;
	cutoutput = 0;
	addPlus = 0;
	//addSpaceBefore = 0;

	while (i < len)
	{
		if (conv[i] == '%')
		{
			i++;
			space_to_skip = 0;
			addPlus = 0;
			while(conv[i] == ' ')
			{
				space_to_skip++;
				i++;
			}
			if(space_to_skip && conv[i] != '+')
				j+=ft_putchar(' ');

			/*if(conv[i] != '+')
				i-=space_to_skip;*/
			//printf("  conv[%d] = %c ", i, conv[i]);
			/*if(conv[i] == ' ' && space_to_skip == 0)
			{
				space_to_skip = 0;
				while(conv[i] == ' ')
				{
					if(conv[i] == '+')
						addPlus = 1;
					space_to_skip++;
					i++;
				}
				if(conv[i] == '0' || conv[i] == '-' || conv[i] == '+'|| conv[i] == '#' || conv[i] == '.'
				|| conv[i] == 'x' || conv[i] == 'X' || conv[i] == 'd' || conv[i] == 'i' || conv[i] == 'u' || conv[i] == '%')
				{
					j += ft_putchar(' ');
				}
				else{
				//	i -= space_to_skip;
					//i++;
				}
			//	printf("396->%c\n", conv[i]);
				//space_to_skip = 0;
				i++;
				printf("\"%d\"", i);
			}*/
			if (conv[i] == '0')
			{
				while(conv[i] == '0')
				{
					//printf("conv[%d] -> %c\n ", i, conv[i]);
					i++;
				}
				//printf("conv + i -> %s\n",conv + i);
				addZero = ft_atoi_for_addZero(conv + i);
				// printf("1\n");
				if (addZero)
					i += lend(addZero);
				// printf("2 i is %d\n", i);
				
				//i++;
			}
			if (conv[i] == '-')
			{
				addZero = 0;
				while(conv[i] == '-')
					i++;
				addSpaceAfter = ft_atoi_for_space(conv + i);
				// printf("\nadd space -> %d\n",addSpaceAfter);
				if (addSpaceAfter)
					i += lend(addSpaceAfter);
				//printf("%s",&s[i]);
				//printf("i -> %d\n", i);
			}
			if (conv[i] == '+')
			{
				//space_to_skip = 0;
				//i -= space_to_skip;
				addPlus = 1;
				while(conv[i] == '+')
					i++;
				while(conv[i] == ' ')
					i++;
			}
			if (conv[i] == '#')
			{
				addOX = 1;
				i++;
			}
			if (conv[i] == '.') // add space in case there is number after dot
			{
				//	cutoutput = ft_at
			}

			if (conv[i] == 'c')
			{
				//printf("\"character\"\n\n");
				c = va_arg(args, int);
			//	j += printSpace(&addSpaceBefore, 1);
				j += ft_putchar(c);
				j += printSpace(&addSpaceAfter, 1);
			}
			if (conv[i] == 's')
			{
				//printf("\"string\"\n");
				//int a = va_arg(args,int );
				//printf("%s\n", va_arg(args,char *));
				s = va_arg(args,char *);
				//printf("4 %s\n", s);
				//j += printSpace(&addSpaceBefore, ft_strlen(s));
				j += ft_putstr(s);
				/*printf("5\n");*/
				j += printSpace(&addSpaceAfter, ft_strlen(s));
				// printf("6\n");
			}
			if (conv[i] == 'p')
			{
				//printf("\"pointer\"\n");
				unsigned long long p = (unsigned long long)va_arg(args, void *);
				j += ft_putstr("0x") + convertfromDec_P(p, "0123456789abcdef");
				j += printSpace(&addSpaceAfter, lenP(p, "0123456789abcdef"));
			}
			if (conv[i] == 'x')
			{
				//printf("\"hexadecimal\"\n");
				x = (unsigned int)va_arg(args, void *);
			//	printf("\"-> %u\"\n",x);
				if (addOX && x)
				{
					j += ft_putstr("0x");
					if (addZero)
						addZero -= 2;
				}
				if (addZero)
				{
					addZero -= lenX(x, "0123456789abcdef"); // we should add the len of hexadecimal number
					while (addZero--)
						j += ft_putchar('0');
				}
				j += convertfromDec_X(x, "0123456789abcdef");
				j += printSpace(&addSpaceAfter, lenX(x, "0123456789abcdef"));
			}
			if (conv[i] == 'X')
			{
				//printf("\"HEXADECIMAL\"\n");
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
					while (addZero--)
						j += ft_putchar('0');
				}
				j += convertfromDec_X(x, "0123456789ABCDEF");
				j += printSpace(&addSpaceAfter, lenX(x, "0123456789ABCDEF"));
			}
			if (conv[i] == 'd' || conv[i] == 'i')
			{
				//printf("\"decimal\"\n");

				d = (long int)va_arg(args, int);
				if(addPlus && d >= 0)
					j += ft_putchar('+');
				if (addZero)
				{
					addZero -= lend(d) + addPlus;
					while (addZero--)
						j += ft_putchar('0');
				}
				j += ft_putnbr(d);
				j += printSpace(&addSpaceAfter, lend(d) + addPlus);
			//	if(addPlus) addPlus = 0;
			}
			if (conv[i] == 'u')
			{
				//printf("\"unsigned\"\n");
				j += ft_putunsignednbr(va_arg(args, unsigned));
				j += printSpace(&addSpaceAfter, j);
			}
			if (conv[i] == '%')
			{
				//printf("\"percentage\"\n");
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

int main(void)
{
	int number = 20;
	char *str = "abcdefghij";
	char c = 'x';
	// printf("|%+12x|\n", number);  
    // ft_printf("|%+12x|\n", number);

	//printf("|%0010d|%-20s|\n", number, str);  
	//ft_printf("|%d|%s|\n", number, str);  

	//printf("|%0010d|%-20s|\n", number, str);  
	//ft_printf("|%0010d|%-20s|\n", number, str); 
	printf("|->%       +  p->%         i|\n", &number, number);
	ft_printf("|->%     +    p->%         i|\n", &number, number);






    //  ft_printf("|%d %s|\n", number, str);
	// printf("|%-10s|\n", str);  
    // ft_printf("|%-10s|\n", str);
	

	/*printf("");
	printf("\n");
	ft_printf("");
	printf("\n=======================================================\n");
	printf("\x01\x02\a\v\b\f\r\n");
	printf("\n");
	ft_printf("\x01\x02\a\v\b\f\r\n");
	printf("\n=======================================================\n");

	printf("%%");
	printf("\n");
	ft_printf("%%");
	printf("\n=======================================================\n");

	printf(" %%");
	printf("\n");
	ft_printf(" %%");
	printf("\n=======================================================\n");

	printf("%%c");
	printf("\n");
	ft_printf("%%c");
	printf("\n=======================================================\n");

	printf("%%%%%%");
	printf("\n");
	ft_printf("%%%%%%");
	printf("\n=======================================================\n");

	printf("%%%c", 'x');
	printf("\n");
	ft_printf("%%%c", 'x');
	printf("\n=======================================================\n");

	printf("%c", 'x');
	printf("\n");
	ft_printf("%c", 'x');
	printf("\n=======================================================\n");

	printf(" %c", 'x');
	printf("\n");
	ft_printf(" %c", 'x');
	printf("\n=======================================================\n");

	printf("%c ", 'x');
	printf("\n");
	ft_printf("%c ", 'x');
	printf("\n=======================================================\n");

	printf("%c%c%c", 'a', '\t', 'b');
	printf("\n");
	ft_printf("%c%c%c", 'a', '\t', 'b');
	printf("\n=======================================================\n");

	printf("%cc%cc%c", 'a', '\t', 'b');
	printf("\n");
	ft_printf("%cc%cc%c", 'a', '\t', 'b');
	printf("\n=======================================================\n");

	printf("%cs%cs%c", 'c', 'b', 'a');
	printf("\n");
	ft_printf("%cs%cs%c", 'c', 'b', 'a');
	printf("\n=======================================================\n");

	printf("%s", "");
	printf("\n");
	ft_printf("%s", "");
	printf("\n=======================================================\n");*/

	/*("%s", (char *)NULL);
	printf("\n");
	ft_printf("%s", (char *)NULL);
	printf("\n=======================================================\n");
	printf("%s", "abcdefg");
	printf("\n");
	ft_printf("%s", "abcdefg");*/
   
	/*printf("%s", "some string with %s hehe");
	printf("\n");
	ft_printf("%s", "some string with %s hehe");
	printf("\n=======================================================\n");

	printf(" %s", "can it handle \t and \n?");
	printf("\n");
	ft_printf(" %s", "can it handle \t and \n?");
	printf("\n=======================================================\n");

	printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	printf("\n");
	ft_printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&");
	printf("\n=======================================================\n");

	printf("%s%s%s", "And ", "some", "joined");
	printf("\n");
	ft_printf("%s%s%s", "And ", "some", "joined");
	printf("\n=======================================================\n");

	printf("%ss%ss%ss", "And ", "some other", "joined");
	printf("\n");
	ft_printf("%ss%ss%ss", "And ", "some other", "joined");
	printf("\n=======================================================\n");

	printf("%p", "");
	printf("\n");
	ft_printf("%p", "");
	printf("\n=======================================================\n");

	printf("%p", NULL);
	printf("\n");
	ft_printf("%p", NULL);
	printf("\n=======================================================\n");

	printf("%p", (void *)-14523);
	printf("\n");
	ft_printf("%p", (void *)-14523);
	printf("\n=======================================================\n");

	printf("0x%p-", (void *)ULONG_MAX);
	printf("\n");
	ft_printf("0x%p-", (void *)ULONG_MAX);
	printf("\n=======================================================\n");

	printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	printf("\n");
	ft_printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	printf("\n=======================================================\n");*/

}