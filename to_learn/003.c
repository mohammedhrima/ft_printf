#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	i;

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
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int ft_printf(const char*conv,...)
{
	int len = ft_strlen(conv);
	int i;

	va_list args;
	va_start(args, conv);
	i = 0;
	while (i < len)
	{
		if(conv[i] == '%')
		{
			i++;
			if(conv[i] == 'c')
			{
				int c = va_arg(args, int);
				ft_putchar(c);
			}
			if(conv[i] == 's')
			{
				char *s = va_arg(args,char*);
				ft_putstr(s);
			}
			if(conv[i] == 'p')
			{
				void *p = va_arg(args, void*);
				printf("%d->%p\n",(int)p,p);
			}
			if(conv[i] == 'd')
			{
				int d = va_arg(args, int);
				printf("%d\n",d);
			}
		}
		i++;
	}
	va_end(args);
	return (0);
}

int main(void)
{
	char mychar = 'x';
	char *str = "abcd";
	char *ptr = NULL;
	int num = 5; 
	int a = 'n';
	ft_putchar(a);
	ft_printf("%c",mychar);
	ft_printf("%s",str);
	ft_printf("%p",ptr);
	ft_printf("%d",num);
}