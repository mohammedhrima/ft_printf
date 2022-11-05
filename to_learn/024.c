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
	j = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (i < ft_strlen(str))
	{
		j += ft_putchar(str[i]);
		if (j < 0)
			return (-1);
		i++;
	}

	return (j);
}

char	*ft_strchr(char *str, char to_find)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == to_find)
			return(str + i);
		i++;
	}
	return (NULL);
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

int ft_atoi(const char *s)
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
	return (neg * res);
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
	if(num >=0 && num < 10)
		i++;
	if(num >= 10)
		i += lend(num / 10) + 1;
	return (i);
}

int lenX(unsigned int num)
{
	int i;
	int j;

	i = 0;
	if (num >= 0 && num < 16)
		i++;
	if (num >= 16)
		i += lenX(num / 16) + 1;
	return (i);
}

int lenP(unsigned long long p)
{
	int i;
	int j;

	i = 0;
	if (p >= 0 && p < 16)
		i++;
	if (p >= 16)
		i += lenP(p / 16) + 1;
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

int printSpace(int *addSpace)
{
	int i;

	i = 0;
	while ((*addSpace)-- > 0)
		i += ft_putchar(' ');
	return (i);
}

int convertfromDec_P(unsigned long long num)
{
	int i;
	int j;
	i = 0;
	char *to;

	to = "0123456789abcdef";
	if (num >= 0 && num < 16)
	{
		j = ft_putchar(to[num]);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= 16)
	{
		j = convertfromDec_P(num / 16);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num % 16]);
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int convertfromDec_X(unsigned int num, char x)
{
	
	int i;
	int j;
	char *to;

	i = 0;
	if(x == 'x')
		to = "0123456789abcdef";
	if(x == 'X')
		to = "0123456789ABCDEF";
	if (num < 0)
	{
		num *= -1;
		j = ft_putchar('-');
		i += j;
	}
	if (num >= 0 && num < 16)
	{
		j = ft_putchar(to[num]);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (num >= 16)
	{
		j = convertfromDec_X(num / 16, x);
		if (j < 0)
			return (-1);
		i += j;
		j = ft_putchar(to[num % 16]);
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

int ft_printf(const char *conv, ...)
{
	int		i;
	int		j;
	int		minus;
	int		zero;
	int		addOx;
	int		space;
	int		plus;
	int		preci;
	int		c;
	char	*s;
	long int d;
	unsigned u;
	unsigned long long p;
	unsigned int x;
	va_list args;

	va_start(args, conv);
	i = 0;
	j = 0;
	while (i < ft_strlen(conv))
	{
		//printf("step 1");
		minus = -1;//add space after
		zero = -1;
		addOx = -1;
		space = -1;
		plus = -1;
		preci = -1;
		if(conv[i] == '%')
		{
			i++;
			while(conv[i] && ft_strchr("-+# 0", conv[i]))
			{
				if(conv[i] == '-')
				{
					zero = -1;
					while(conv[i] == '-')
						i++;
					minus = ft_atoi(conv + i);
					if(conv[i] >= '0' && conv[i] <= '9')
						i += lend((long)minus);  //1 dyal minus
		
				}
				else if(conv[i] == '+')
				{
					space = -1;
					plus = 1;
					i++;
				}
				else if(conv[i] == '0')
				{	zero = ft_atoi(conv+i+1);
					i += lend(zero) + 1;
				}
				else if(conv[i] == '.')
					preci = ft_atoi(conv + i + 1);
				else if(conv[i] == '#')
					addOx = 1;
				else if(conv[i] == ' ') //check + sign because it make some change to space
				{
					space = ft_atoi(conv + i + 1);
				}
		
			}
			if(conv[i] == 'c')
			{
				c = va_arg(args,int);
				j += ft_putchar(c);
				minus -= 1;//len of char
				while(minus-- > 0)
					j += ft_putchar(' ');
			}
			else if (conv[i] == 's')
			{
				s = va_arg(args, char *);
				j += ft_putstr(s);
				minus -= ft_strlen(s);
				while(minus-- > 0)
					j += ft_putchar(' ');
			}
			if(conv[i] == 'p')
			{
				p = (unsigned long long)va_arg(args, void*);
				j += ft_putstr("0x") + convertfromDec_P(p);
				minus -= (lenP(p) + 2);
				while(minus-- > 0)
					j += ft_putchar(' ');
			}
			if(conv[i] == 'x' || conv[i] == 'X')
			{
				x = (unsigned int)va_arg(args, void *);
				j += convertfromDec_X(x,conv[i]);
				minus -= lenX(x);
				while(minus-- > 0)
					j += ft_putchar(' ');
			}
			if(conv[i] == 'd' || conv[i] == 'i')
			{
				d = (long int)va_arg(args, int);
				if(plus>0 && d >= 0)
					j+= ft_putchar('+');
				if(d < 0)
				{
					j += ft_putchar('-');
					d = -d;
					zero--;
				}
				zero -= lend(d);
				while(zero-- > 0)
					j += ft_putchar('0');
				j += ft_putnbr(d);
				minus -= lend(d);
				while(minus-- > 0)
					j += ft_putchar(' ');		
			}
			if (conv[i] == 'u')
			{
				u = va_arg(args, unsigned);
				if(plus>0)
					j+= ft_putchar('+');
				zero -= lenU(u);
				while(zero-- > 0)
					j += ft_putchar('0');
				j += ft_putunsignednbr(u);
				minus -= lenU(u);
				while(minus-- > 0)
					j += ft_putchar(' ');
			}
			if (conv[i] == '%')
			{
				j += ft_putchar('%');
			//	j += printSpace(&minus, j);
			}
			i++;
		}
		else
		{
		//	ft_putchar('\\');
			j += ft_putchar(conv[i]);
			//printf("\nI did write %d char \n", j);
			//j += ft_putchar('x');
		//	ft_putchar('\\');
			i++;
		}
	}
	
	va_end(args);
	return(j);
}

//0 flag main
/*int main(void)
{
	int n,m;


	//digits
	// n = printf(" %01d ", 0);
	// printf("\n");
	// m = ft_printf(" %01d ", 0);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %02d ", -1);
	// printf("\n");
	// m = ft_printf(" %02d ", -1);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %04d ", 9);
	// printf("\n");
	// m = ft_printf(" %04d ", 9);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %01d ", 10);
	// printf("\n");
	// m = ft_printf(" %01d ", 10);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %02d ", 11);
	// printf("\n");
	// m = ft_printf(" %02d ", 11);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %03d ", 15);
	// printf("\n");
	// m = ft_printf(" %03d ", 15);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %04d ", -16);
	// printf("\n");
	// m = ft_printf(" %04d ", -16);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %05d ", 17);
	// printf("\n");
	// m = ft_printf(" %05d ", 17);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %01d ", 99);
	// printf("\n");
	// m = ft_printf(" %01d ", 99);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %02d ", 100);
	// printf("\n");
	// m = ft_printf(" %02d ", 100);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %03d ", 101);
	// printf("\n");
	// m = ft_printf(" %03d ", 101);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %01d ", -9);
	// printf("\n");
	// m = ft_printf(" %01d ", -9);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %02d ", -10);
	// printf("\n");
	// m = ft_printf(" %02d ", -10);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %03d ", -11);
	// printf("\n");
	// m = ft_printf(" %03d ", -11);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %04d ", -14);
	// printf("\n");
	// m = ft_printf(" %04d ", -14);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %05d ", -15);
	// printf("\n");
	// m = ft_printf(" %05d ", -15);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %06d ", -16);
	// printf("\n");
	// m = ft_printf(" %06d ", -16);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %01d ", -99);
	// printf("\n");
	// m = ft_printf(" %01d ", -99);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %02d ", -100);
	// printf("\n");
	// m = ft_printf(" %02d ", -100);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %03d ", -101);
	// printf("\n");
	// m = ft_printf(" %03d ", -101);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %09d ", INT_MAX);
	// printf("\n");
	// m = ft_printf(" %09d ", INT_MAX);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %010d ", INT_MIN);
	// printf("\n");
	// m = ft_printf(" %010d ", INT_MIN);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %011d ", LONG_MAX);
	// printf("\n");
	// m = ft_printf(" %011d ", LONG_MAX);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %012d ", LONG_MIN);
	// printf("\n");
	// m = ft_printf(" %012d ", LONG_MIN);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %013d ", UINT_MAX);
	// printf("\n");
	// m = ft_printf(" %013d ", UINT_MAX);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %014d ", ULONG_MAX);
	// printf("\n");
	// m = ft_printf(" %014d ", ULONG_MAX);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	// n = printf(" %015d ", 9223372036854775807LL);
	// printf("\n");
	// m = ft_printf(" %015d ", 9223372036854775807LL);
	// printf("\n");
	// printf("n = %d m=%d\n",n,m);
	// printf("\n=======================\n");
	//integers
// n = printf(" %01i ", 0);
// 	printf("\n");
// 	m = ft_printf(" %01i ", 0);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %02i ", -1);
// 	printf("\n");
// 	m = ft_printf(" %02i ", -1);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %03i ", 1);
// 	printf("\n");
// 	m = ft_printf(" %03i ", 1);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %04i ", 9);
// 	printf("\n");
// 	m = ft_printf(" %04i ", 9);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %01i ", 10);
// 	printf("\n");
// 	m = ft_printf(" %01i ", 10);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %02i ", 11);
// 	printf("\n");
// 	m = ft_printf(" %02i ", 11);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %03i ", 15);
// 	printf("\n");
// 	m = ft_printf(" %03i ", 15);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %04i ", 16);
// 	printf("\n");
// 	m = ft_printf(" %04i ", 16);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %05i ", 17);
// 	printf("\n");
// 	m = ft_printf(" %05i ", 17);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %01i ", 99);
// 	printf("\n");
// 	m = ft_printf(" %01i ", 99);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %02i ", 100);
// 	printf("\n");
// 	m = ft_printf(" %02i ", 100);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %03i ", 101);
// 	printf("\n");
// 	m = ft_printf(" %03i ", 101);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %01i ", -9);
// 	printf("\n");
// 	m = ft_printf(" %01i ", -9);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %02i ", -10);
// 	printf("\n");
// 	m = ft_printf(" %02i ", -10);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %03i ", -11);
// 	printf("\n");
// 	m = ft_printf(" %03i ", -11);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %04i ", -14);
// 	printf("\n");
// 	m = ft_printf(" %04i ", -14);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %05i ", -15);
// 	printf("\n");
// 	m = ft_printf(" %05i ", -15);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %06i ", -16);
// 	printf("\n");
// 	m = ft_printf(" %06i ", -16);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %01i ", -99);
// 	printf("\n");
// 	m = ft_printf(" %01i ", -99);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %02i ", -100);
// 	printf("\n");
// 	m = ft_printf(" %02i ", -100);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %03i ", -101);
// 	printf("\n");
// 	m = ft_printf(" %03i ", -101);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %09i ", INT_MAX);
// 	printf("\n");
// 	m = ft_printf(" %09i ", INT_MAX);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %010i ", INT_MIN);
// 	printf("\n");
// 	m = ft_printf(" %010i ", INT_MIN);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %011i ", LONG_MAX);
// 	printf("\n");
// 	m = ft_printf(" %011i ", LONG_MAX);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %012i ", LONG_MIN);
// 	printf("\n");
// 	m = ft_printf(" %012i ", LONG_MIN);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %013i ", UINT_MAX);
// 	printf("\n");
// 	m = ft_printf(" %013i ", UINT_MAX);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %014i ", ULONG_MAX);
// 	printf("\n");
// 	m = ft_printf(" %014i ", ULONG_MAX);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %015i ", 9223372036854775807LL);
// 	printf("\n");
// 	m = ft_printf(" %015i ", 9223372036854775807LL);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
// 	n = printf(" %09i %010i %011i %012i %013i %014i %015i", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 	printf("\n");
// 	m = ft_printf(" %09i %010i %011i %012i %013i %014i %015i", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 	printf("\n");
// 	printf("n=%d m=%d",n,m);
// 	printf("\n==============================\n\n");
	//unsigned
	// n = printf(" %01u ", 0);
	// printf("\n");
	// m = ft_printf(" %01u ", 0);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %02u ", -1);
	// printf("\n");
	// m = ft_printf(" %02u ", -1);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %03u ", 1);
	// printf("\n");
	// m = ft_printf(" %03u ", 1);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %04u ", 9);
	// printf("\n");
	// m = ft_printf(" %04u ", 9);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %01u ", 10);
	// printf("\n");
	// m = ft_printf(" %01u ", 10);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %02u ", 11);
	// printf("\n");
	// m = ft_printf(" %02u ", 11);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %03u ", 15);
	// printf("\n");
	// m = ft_printf(" %03u ", 15);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %04u ", 16);
	// printf("\n");
	// m = ft_printf(" %04u ", 16);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %05u ", 17);
	// printf("\n");
	// m = ft_printf(" %05u ", 17);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %01u ", 99);
	// printf("\n");
	// m = printf(" %01u ", 99);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %02u ", 100);
	// printf("\n");
	// m = printf(" %02u ", 100);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %03u ", 101);
	// printf("\n");
	// m = printf(" %03u ", 101);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %01u ", -9);
	// printf("\n");
	// m = printf(" %01u ", -9);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %02u ", -10);
	// printf("\n");
	// m = printf(" %02u ", -10);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %03u ", -11);
	// printf("\n");
	// m = printf(" %03u ", -11);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %04u ", -14);
	// printf("\n");
	// m = printf(" %04u ", -14);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %05u ", -15);
	// printf("\n");
	// m = printf(" %05u ", -15);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %06u ", -16);
	// printf("\n");
	// m = printf(" %06u ", -16);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %01u ", -99);
	// printf("\n");
	// m = printf(" %01u ", -99);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %02u ", -100);
	// printf("\n");
	// m = printf(" %02u ", -100);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %03u ", -101);
	// printf("\n");
	// m = printf(" %03u ", -101);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %09u ", INT_MAX);
	// printf("\n");
	// m = printf(" %09u ", INT_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %010u ", INT_MIN);
	// printf("\n");
	// m = printf(" %010u ", INT_MIN);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %011u ", LONG_MAX);
	// printf("\n");
	// m = printf(" %011u ", LONG_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %012u ", LONG_MIN);
	// printf("\n");
	// m = printf(" %012u ", LONG_MIN);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %013u ", UINT_MAX);
	// printf("\n");
	// m = printf(" %013u ", UINT_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %014u ", ULONG_MAX);
	// printf("\n");
	// m = printf(" %014u ", ULONG_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %015u ", 9223372036854775807LL);
	// printf("\n");
	// m = printf(" %015u ", 9223372036854775807LL);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
	// n = printf(" %09u %010u %011u %012u %013u %014u %015u", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = printf(" %09u %010u %011u %012u %013u %014u %015u", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf("n=%d m=%d\n");
	// printf("==========================\n\n");
}*/



//plus flag main
/*int main(void)
{
	//int n,m;
	//digits
	
	// n = printf(" %+d ", 0);
	// printf("\n");
	// m = ft_printf(" %+d ", 0);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -1);
	// printf("\n");
	// m = ft_printf(" %+d ", -1);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 9);
	// printf("\n");
	// m = ft_printf(" %+d ", 9);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 10);
	// printf("\n");
	// m = ft_printf(" %+d ", 10);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 11);
	// printf("\n");
	// m = ft_printf(" %+d ", 11);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 15);
	// printf("\n");
	// m = ft_printf(" %+d ", 15);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 16);
	// printf("\n");
	// m = ft_printf(" %+d ", 16);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 17);
	// printf("\n");
	// m = ft_printf(" %+d ", 17);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 99);
	// printf("\n");
	// m = ft_printf(" %+d ", 99);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 100);
	// printf("\n");
	// m = ft_printf(" %+d ", 100);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 101);
	// printf("\n");
	// m = ft_printf(" %+d ", 101);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -9);
	// printf("\n");
	// m = ft_printf(" %+d ", -9);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -10);
	// printf("\n");
	// m = ft_printf(" %+d ", -10);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -11);
	// printf("\n");
	// m = ft_printf(" %+d ", -11);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -14);
	// printf("\n");
	// m = ft_printf(" %+d ", -14);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -15);
	// printf("\n");
	// m = ft_printf(" %+d ", -15);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -16);
	// printf("\n");
	// m = ft_printf(" %+d ", -16);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -99);
	// printf("\n");
	// m = ft_printf(" %+d ", -99);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -100);
	// printf("\n");
	// m = ft_printf(" %+d ", -100);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", -101);
	// printf("\n");
	// m = ft_printf(" %+d ", -101);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", INT_MAX);
	// printf("\n");
	// m = ft_printf(" %+d ", INT_MAX);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", INT_MIN);
	// printf("\n");
	// m = ft_printf(" %+d ", INT_MIN);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", LONG_MAX);
	// printf("\n");
	// m = ft_printf(" %+d ", LONG_MAX);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", LONG_MIN);
	// printf("\n");
	// m = ft_printf(" %+d ", LONG_MIN);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", UINT_MAX);
	// printf("\n");
	// m = ft_printf(" %+d ", UINT_MAX);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", ULONG_MAX);
	// printf("\n");
	// m = ft_printf(" %+d ", ULONG_MAX);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d ", 9223372036854775807LL);
	// printf("\n");
	// m = ft_printf(" %+d ", 9223372036854775807LL);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf(" %+d %+d %+d %+d %+d %+d %+d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = ft_printf(" %+d %+d %+d %+d %+d %+d %+d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// //intgers
	// n = printf(" %+i ", 0);
	// printf("\n");
	// m = ft_printf(" %+i ", 0);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -1);
	// printf("\n");
	// m = ft_printf(" %+i ", -1);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 1);
	// printf("\n");
	// m = ft_printf(" %+i ", 1);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 9);
	// printf("\n");
	// m = ft_printf(" %+i ", 9);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 10);
	// printf("\n");
	// m = ft_printf(" %+i ", 10);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 11);
	// printf("\n");
	// m = ft_printf(" %+i ", 11);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 15);
	// printf("\n");
	// m = ft_printf(" %+i ", 15);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 16);
	// printf("\n");
	// m = ft_printf(" %+i ", 16);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 17);
	// printf("\n");
	// m = ft_printf(" %+i ", 17);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 99);
	// printf("\n");
	// m = ft_printf(" %+i ", 99);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 100);
	// printf("\n");
	// m = ft_printf(" %+i ", 100);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 101);
	// printf("\n");
	// m = ft_printf(" %+i ", 101);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -9);
	// printf("\n");
	// m = ft_printf(" %+i ", -9);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -10);
	// printf("\n");
	// m = ft_printf(" %+i ", -10);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -11);
	// printf("\n");
	// m = ft_printf(" %+i ", -11);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -14);
	// printf("\n");
	// m = ft_printf(" %+i ", -14);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -15);
	// printf("\n");
	// m = ft_printf(" %+i ", -15);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -16);
	// printf("\n");
	// m = ft_printf(" %+i ", -16);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -99);
	// printf("\n");
	// m = ft_printf(" %+i ", -99);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -100);
	// printf("\n");
	// m = ft_printf(" %+i ", -100);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", -101);
	// printf("\n");
	// m = ft_printf(" %+i ", -101);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", INT_MAX);
	// printf("\n");
	// m = ft_printf(" %+i ", INT_MAX);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", INT_MIN);
	// printf("\n");
	// m = ft_printf(" %+i ", INT_MIN);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", LONG_MAX);
	// printf("\n");
	// m = ft_printf(" %+i ", LONG_MAX);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", LONG_MIN);
	// printf("\n");
	// m = ft_printf(" %+i ", LONG_MIN);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", UINT_MAX);
	// printf("\n");
	// m = ft_printf(" %+i ", UINT_MAX);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", ULONG_MAX);
	// printf("\n");
	// m = ft_printf(" %+i ", ULONG_MAX);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i ", 9223372036854775807LL);
	// printf("\n");
	// m = ft_printf(" %+i ", 9223372036854775807LL);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
	// n = printf(" %+i %+i %+i %+i %+i %+i %+i", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = ft_printf(" %+i %+i %+i %+i %+i %+i %+i", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf("n = %d m = %d",n,m);
	// printf("\n=======================\n\n");
}*/

//minus flag main
/*int main()
{
	int n,m;
	
	//Characters
	// n = printf("%-1c", '0');
	// printf("\n");
	// m = ft_printf("%-1c", '0');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");

	// n = printf(" %-2c ", '0');
	// printf("\n");
	// m = ft_printf(" %-2c ", '0');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3c", '0' - 256);
	// printf("\n");
	// m = ft_printf(" %-3c", '0' - 256);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("%-4c ", '0' + 256);
	// printf("\n");
	// m = ft_printf("%-4c ", '0' + 256);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1c %-2c %-3c ", '0', 0, '1');
	// printf("\n");
	// m = ft_printf(" %-1c %-2c %-3c ", '0', 0, '1');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1c %-2c %-3c ", ' ', ' ', ' ');
	// printf("\n");
	// m = ft_printf(" %-1c %-2c %-3c ", ' ', ' ', ' ');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1c %-2c %-3c ", '1', '2', '3');
	// printf("\n");
	// m = ft_printf(" %-1c %-2c %-3c ", '1', '2', '3');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1c %-2c %-3c ", '2', '1', 0);
	// printf("\n");
	// m = ft_printf(" %-1c %-2c %-3c ", '2', '1', 0);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	
	// n = printf(" %-1c %-2c %-3c ", 0, '1', '2');
	// printf("\n");
	// m = ft_printf(" %-1c %-2c %-3c ", 0, '1', '2');
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);

	//Strings
	// n = printf("|%-1s|", "");
	// printf("\n");
	// m = ft_printf("|%-1s|", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");

	// n = printf("|+%-2s|", "");
	// printf("\n");
	// m = ft_printf("|+%-2s|", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("|%-3s+|", "");
	// printf("\n");
	// m = ft_printf("|%-3s+|", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("|%-s+|", "");
	// printf("\n");
	// m = ft_printf("|%-s+|", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("|+%-1s+|", "-");
	// printf("\n");
	// m = ft_printf("|+%-1s+|", "-");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("|-%-1s-%-2s-|", "", "-");
	// printf("\n");
	// m = ft_printf("|-%-1s-%-2s-|", "", "-");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-3s %-4s |", "ABC", "");
	// printf("\n");
	// m = ft_printf("| %-3s %-4s |", "ABC", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-2s %-3s %-4s %-5s |", "ABC", "", "D", "");
	// printf("\n");
	// m = ft_printf("| %-2s %-3s %-4s %-5s |", "ABC", "", "D", "");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	
	// n = printf("| %-3s %-3s %-4s %-5s %-3s |", "ABC", "", "D", "", "EF");
	// printf("\n");
	// m = ft_printf("| %-3s %-3s %-4s %-5s %-3s |", "ABC", "", "D", "", "EF");
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);

	//Pointer
	// n = printf("| %-2p |\n", (void*)-1);
	// printf("\n");
	// m = ft_printf("| %-2p |\n", (void*)-1);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");

	// n = printf("| %-2p |\n", (void*)1);
	// printf("\n");
	// m = ft_printf("| %-2p |\n", (void*)1);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-3p |\n", (void*)16);
	// printf("\n");
	// m = ft_printf("| %-3p |\n", (void*)16);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-4p |\n", (void*)17);
	// printf("\n");
	// m = ft_printf("| %-4p |\n", (void*)17);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-9p %-10p |\n", (void*)LONG_MIN, (void*)LONG_MAX);
	// printf("\n");
	// m = ft_printf("| %-9p %-10p |\n", (void*)LONG_MIN, (void*)LONG_MAX);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-11p %-12p |\n", (void*)INT_MIN, (void*)INT_MAX);
	// printf("\n");
	// m = ft_printf("| %-11p %-12p |\n", (void*)INT_MIN, (void*)INT_MAX);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-13p %-14p |\n", (void*)ULONG_MAX, (void*)-ULONG_MAX);
	// printf("\n");
	// m = ft_printf("| %-13p %-14p |\n", (void*)ULONG_MAX, (void*)-ULONG_MAX);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-1p %-2p |\n", NULL, NULL);
	// printf("\n");
	// m = ft_printf("| %-1p %-2p |\n", NULL, NULL);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);

	//Digits
	// n = printf(" %-1d ", 0);
	// printf("\n");
	// m = ft_printf(" %-1d ", 0);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");

	// n = printf(" %-2d ", -1);
	// printf("\n");
	// m = ft_printf(" %-2d ", -1);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3d ", 1);
	// printf("\n");
	// m = ft_printf(" %-3d ", 1);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-4d ", 9);
	// printf("\n");
	// m = ft_printf(" %-4d ", 9);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1d ", 10);
	// printf("\n");
	// m = ft_printf(" %-1d ", 10);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-2d ", 11);
	// printf("\n");
	// m = ft_printf(" %-2d ", 11);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3d ", 15);
	// printf("\n");
	// m = ft_printf(" %-3d ", 15);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-4d ", 16);
	// printf("\n");
	// m = ft_printf(" %-4d ", 16);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-5d ", 17);
	// printf("\n");
	// m = ft_printf(" %-5d ", 17);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1d ", 99);
	// printf("\n");
	// m = ft_printf(" %-1d ", 99);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-2d ", 100);
	// printf("\n");
	// m = ft_printf(" %-2d ", 100);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3d ", 101);
	// printf("\n");
	// m = ft_printf(" %-3d ", 101);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1d ", -9);
	// printf("\n");
	// m = ft_printf(" %-1d ", -9);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-2d ", -10);
	// printf("\n");
	// m = ft_printf(" %-2d ", -10);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3d ", -11);
	// printf("\n");
	// m = ft_printf(" %-3d ", -11);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-4d ", -14);
	// printf("\n");
	// m = ft_printf(" %-4d ", -14);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-5d ", -15);
	// printf("\n");
	// m = ft_printf(" %-5d ", -15);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-6d ", -16);
	// printf("\n");
	// m = ft_printf(" %-6d ", -16);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-1d ", -99);
	// printf("\n");
	// m = ft_printf(" %-1d ", -99);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-2d ", -100);
	// printf("\n");
	// m = ft_printf(" %-2d ", -100);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf(" %-3d ", -101);
	// printf("\n");
	// m = ft_printf(" %-3d ", -101);
	// printf("\n");
	// printf("n = %d | m = %d\n\n",n,m);
	// printf("===============================\n");
	
	// n = printf("| %-9d ", INT_MAX);
	// printf("\n");
	// m = ft_printf("| %-9d ", INT_MAX);
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");
	// n = printf("| %-10d ", INT_MIN);
	// printf("\n");
	// m = ft_printf("| %-10d ", INT_MIN);
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");

	// n = printf("| %-13d ", UINT_MAX);
	// printf("\n");
	// m = ft_printf("| %-13d ", UINT_MAX);
	// printf("n = %d m = %d\n",n,m);

	// printf("\n==========================\n");
	// n = printf("| %-9d %-10d %-14d %-15d", INT_MAX, INT_MIN,  0, -42);
	// printf("\n");
	// m = ft_printf("| %-9d %-10d %-14d %-15d", INT_MAX, INT_MIN,  0, -42);
	// printf("n = %d m = %d\n",n,m);
	// printf("\n==========================\n");

	//intgers
	// n = printf(" %-1i ", 0);
	// printf("\n");
	// m = printf(" %-1i ", 0);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-2i ", -1);
	// printf("\n");
	// m = printf(" %-2i ", -1);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-3i ", 1);
	// printf("\n");
	// m = printf(" %-3i ", 1);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-4i ", 9);
	// printf("\n");
	// m = printf(" %-4i ", 9);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-1i ", 10);
	// printf("\n");
	// m = printf(" %-1i ", 10);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-2i ", 11);
	// printf("\n");
	// m = printf(" %-2i ", 11);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-3i ", 15);
	// printf("\n");
	// m = printf(" %-3i ", 15);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-4i ", 16);
	// printf("\n");
	// m = printf(" %-4i ", 16);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-5i ", 17);
	// printf("\n");
	// m = printf(" %-5i ", 17);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-1i ", 99);
	// printf("\n");
	// m = printf(" %-1i ", 99);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-2i ", 100);
	// printf("\n");
	// m = printf(" %-2i ", 100);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-3i ", 101);
	// printf("\n");
	// m = printf(" %-3i ", 101);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-1i ", -9);
	// printf("\n");
	// m = printf(" %-1i ", -9);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-2i ", -10);
	// printf("\n");
	// m = printf(" %-2i ", -10);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-3i ", -11);
	// printf("\n");
	// m = printf(" %-3i ", -11);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-4i ", -14);
	// printf("\n");
	// m = printf(" %-4i ", -14);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-5i ", -15);
	// printf("\n");
	// m = printf(" %-5i ", -15);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-6i ", -16);
	// printf("\n");
	// m = printf(" %-6i ", -16);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-1i ", -99);
	// printf("\n");
	// m = printf(" %-1i ", -99);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-2i ", -100);
	// printf("\n");
	// m = printf(" %-2i ", -100);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-3i ", -101);
	// printf("\n");
	// m = printf(" %-3i ", -101);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-9i ", INT_MAX);
	// printf("\n");
	// m = printf(" %-9i ", INT_MAX);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-10i ", INT_MIN);
	// printf("\n");
	// m = printf(" %-10i ", INT_MIN);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-13i ", UINT_MAX);
	// printf("\n");
	// m = printf(" %-13i ", UINT_MAX);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	// n = printf(" %-9i %-10i %-14i %-15i", INT_MAX, INT_MIN, 0, -42);
	// printf("\n");
	// m = printf(" %-9i %-10i %-14i %-15i", INT_MAX, INT_MIN, 0, -42);
	// printf("\nn = %d m = %d\n", n, m);
	// printf("=====================\n");

	//unsigned
	// n = printf("\n %-1u ", 0);
	// m = ft_printf("\n %-1u ", 0);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-2u ", -1);
	// m = ft_printf("\n %-2u ", -1);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-3u ", 1);
	// m = ft_printf("\n %-3u ", 1);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-4u ", 9);
	// m = ft_printf("\n %-4u ", 9);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-1u ", 10);
	// m = ft_printf("\n %-1u ", 10);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-2u ", 11);
	// m = ft_printf("\n %-2u ", 11);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-3u ", 15);
	// m = ft_printf("\n %-3u ", 15);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-4u ", 16);
	// m = ft_printf("\n %-4u ", 16);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-5u ", 17);
	// m = ft_printf("\n %-5u ", 17);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-1u ", 99);
	// m = ft_printf("\n %-1u ", 99);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-2u ", 100);
	// m = ft_printf("\n %-2u ", 100);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-3u ", 101);
	// m = ft_printf("\n %-3u ", 101);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-1u ", -9);
	// m = ft_printf("\n %-1u ", -9);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-2u ", -10);
	// m = ft_printf("\n %-2u ", -10);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-3u ", -11);
	// m = ft_printf("\n %-3u ", -11);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-4u ", -14);
	// m = ft_printf("\n %-4u ", -14);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-5u ", -15);
	// m = ft_printf("\n %-5u ", -15);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-6u ", -16);
	// m = ft_printf("\n %-6u ", -16);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-1u ", -99);
	// m = ft_printf("\n %-1u ", -99);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-2u ", -100);
	// m = ft_printf("\n %-2u ", -100);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-3u ", -101);
	// m = ft_printf("\n %-3u ", -101);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-9u ", INT_MAX);
	// m = ft_printf("\n %-9u ", INT_MAX);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-10u ", INT_MIN);
	// m = ft_printf("\n %-10u ", INT_MIN);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-11u ", LONG_MAX);
	// m = ft_printf("\n %-11u ", LONG_MAX);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-12u ", LONG_MIN);
	// m = ft_printf("\n %-12u ", LONG_MIN);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-13u ", UINT_MAX);
	// m = ft_printf("\n %-13u ", UINT_MAX);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-14u ", ULONG_MAX);
	// m = ft_printf("\n %-14u ", ULONG_MAX);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-15u ", 9223372036854775807LL);
	// m = ft_printf("\n %-15u ", 9223372036854775807LL);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");
	// n = printf("\n %-9u %-10u %-11u %-12u %-13u %-14u %-15u", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = ft_printf("\n %-9u %-10u %-11u %-12u %-13u %-14u %-15u", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\nn=%d m=%d",n,m);
	// printf("\n===========================\n");

	//hexadecimal
	// n = printf(" %-1x ", 0);
	// printf("\n");
	// m = ft_printf(" %-1x ", 0);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-2x ", -1);
	// printf("\n");
	// m = ft_printf(" %-2x ", -1);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-3x ", 1);
	// printf("\n");
	// m = ft_printf(" %-3x ", 1);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-4x ", 9);
	// printf("\n");
	// m = ft_printf(" %-4x ", 9);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-1x ", 10);
	// printf("\n");
	// m = ft_printf(" %-1x ", 10);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-2x ", 11);
	// printf("\n");
	// m = ft_printf(" %-2x ", 11);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-3x ", 15);
	// printf("\n");
	// m = ft_printf(" %-3x ", 15);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-4x ", 16);
	// printf("\n");
	// m = ft_printf(" %-4x ", 16);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-5x ", 17);
	// printf("\n");
	// m = ft_printf(" %-5x ", 17);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-1x ", 99);
	// printf("\n");
	// m = ft_printf(" %-1x ", 99);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-2x ", 100);
	// printf("\n");
	// m = ft_printf(" %-2x ", 100);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-3x ", 101);
	// printf("\n");
	// m = ft_printf(" %-3x ", 101);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-1x ", -9);
	// printf("\n");
	// m = ft_printf(" %-1x ", -9);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-2x ", -10);
	// printf("\n");
	// m = ft_printf(" %-2x ", -10);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-3x ", -11);
	// printf("\n");
	// m = ft_printf(" %-3x ", -11);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-4x ", -14);
	// printf("\n");
	// m = ft_printf(" %-4x ", -14);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-5x ", -15);
	// printf("\n");
	// m = ft_printf(" %-5x ", -15);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-6x ", -16);
	// printf("\n");
	// m = ft_printf(" %-6x ", -16);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-1x ", -99);
	// printf("\n");
	// m = ft_printf(" %-1x ", -99);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-2x ", -100);
	// printf("\n");
	// m = ft_printf(" %-2x ", -100);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-3x ", -101);
	// printf("\n");
	// m = ft_printf(" %-3x ", -101);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-9x ", INT_MAX);
	// printf("\n");
	// m = ft_printf(" %-9x ", INT_MAX);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-10x ", INT_MIN);
	// printf("\n");
	// m = ft_printf(" %-10x ", INT_MIN);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-11x ", LONG_MAX);
	// printf("\n");
	// m = ft_printf(" %-11x ", LONG_MAX);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-12x ", LONG_MIN);
	// printf("\n");
	// m = ft_printf(" %-12x ", LONG_MIN);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-13x ", UINT_MAX);
	// printf("\n");
	// m = ft_printf(" %-13x ", UINT_MAX);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-14x ", ULONG_MAX);
	// printf("\n");
	// m = ft_printf(" %-14x ", ULONG_MAX);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-15x ", 9223372036854775807LL);
	// printf("\n");
	// m = ft_printf(" %-15x ", 9223372036854775807LL);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");
	// n = printf(" %-9x %-10x %-11x %-12x %-13x %-14x %-15x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = ft_printf(" %-9x %-10x %-11x %-12x %-13x %-14x %-15x", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf("n = %d m= %d\n",n,m);
	// printf("\n=================================\n\n");

	//HEXADECIAML
	// n = printf(" %-1X ", 0);
	// printf("\n");
	// m = printf(" %-1X ", 0);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-2X ", -1);
	// printf("\n");
	// m = printf(" %-2X ", -1);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-3X ", 1);
	// printf("\n");
	// m = printf(" %-3X ", 1);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-4X ", 9);
	// printf("\n");
	// m = printf(" %-4X ", 9);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-1X ", 10);
	// printf("\n");
	// m = printf(" %-1X ", 10);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-2X ", 11);
	// printf("\n");
	// m = printf(" %-2X ", 11);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-3X ", 15);
	// printf("\n");
	// m = printf(" %-3X ", 15);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-4X ", 16);
	// printf("\n");
	// m = printf(" %-4X ", 16);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-5X ", 17);
	// printf("\n");
	// m = printf(" %-5X ", 17);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-1X ", 99);
	// printf("\n");
	// m = printf(" %-1X ", 99);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-2X ", 100);
	// printf("\n");
	// m = printf(" %-2X ", 100);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-3X ", 101);
	// printf("\n");
	// m = printf(" %-3X ", 101);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-1X ", -9);
	// printf("\n");
	// m = printf(" %-1X ", -9);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-2X ", -10);
	// printf("\n");
	// m = printf(" %-2X ", -10);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-3X ", -11);
	// printf("\n");
	// m = printf(" %-3X ", -11);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-4X ", -14);
	// printf("\n");
	// m = printf(" %-4X ", -14);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-5X ", -15);
	// printf("\n");
	// m = printf(" %-5X ", -15);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-6X ", -16);
	// printf("\n");
	// m = printf(" %-6X ", -16);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-1X ", -99);
	// printf("\n");
	// m = printf(" %-1X ", -99);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-2X ", -100);
	// printf("\n");
	// m = printf(" %-2X ", -100);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-3X ", -101);
	// printf("\n");
	// m = printf(" %-3X ", -101);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-9X ", INT_MAX);
	// printf("\n");
	// m = printf(" %-9X ", INT_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-10X ", INT_MIN);
	// printf("\n");
	// m = printf(" %-10X ", INT_MIN);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-11X ", LONG_MAX);
	// printf("\n");
	// m = printf(" %-11X ", LONG_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-12X ", LONG_MIN);
	// printf("\n");
	// m = printf(" %-12X ", LONG_MIN);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-13X ", UINT_MAX);
	// printf("\n");
	// m = printf(" %-13X ", UINT_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-14X ", ULONG_MAX);
	// printf("\n");
	// m = printf(" %-14X ", ULONG_MAX);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-15X ", 9223372036854775807LL);
	// printf("\n");
	// m = printf(" %-15X ", 9223372036854775807LL);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
	// n = printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// m = printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf("n=%d m=%d\n",n,m);
	// printf("\n=============================\n");
};*/

