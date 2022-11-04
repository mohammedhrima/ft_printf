#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_putchar(char c)
{
	write(1, &c,1);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void convertfromDec(int num, char *to)
{
	int len = ft_strlen(to);
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

int power(int num , int power)
{
	int res;
	res = 1;
	while (power-- >= 1)
		res*=num;
	return(res);
}

int convertoDec(char *num, char *from)
{
	int i;
	int j;
	int len;
	int res;
	int num1;

	i = ft_strlen(num);
	len = ft_strlen(from);
	res = 0;
	j = 0;
	if(num[j] == '-')
		j++;
	while (i > j)
	{
		printf("%d -> %c\n",ft_strlen(num) - i,  num[i-1]);

		if(num[i - 1] >= 'A' && num[i - 1] <= 'Z' )
			num1 = num[i - 1] - 'A' + 10;
		else
			num1 = num[i - 1] - '0';
		
		res = res + (num1)*power(len, ft_strlen(num) - i);
		printf("%d x %d^%d + \n",num1 , len, ft_strlen(num) - i  );
		i--;
	}
	if(j) res *= -1;
	return(res);
}

void ConvertBase(char *num, char *from , char *to)
{
	int num1 = convertoDec(num, from);
	convertfromDec(num1, to);
}


void	ft_putnbr(int num)
{
	if (num == INT_MIN)
	{
		ft_putstr("-2147483648");
		return;
	}
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

int main(void)
{
	convertfromDec(200, "0123456789ABCDEF");
	printf("\n");
	int n = convertoDec("1F6", "0123456789ABCDEF");
	printf("\n-> %d\n", n);
	ConvertBase("-1F6","0123456789ABCDEF","01234567");
	
}