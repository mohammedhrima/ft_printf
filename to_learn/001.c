#include <stdio.h>
#include <stdarg.h>

int max(int num_args,...)
{
	va_list args;
	va_start(args, num_args);
	int i = 0;
	int max;
	while (i < num_args )
	{
		int x = va_arg(args, int);
		if(!i) max = x;
		else if( x > max) max = x;
		printf("x: %d\n",x);
		i++;
	}
	va_end(args);
	return(max);
}

int main(void)
{
	int res = max(5,(25,68,79,16,58));
}