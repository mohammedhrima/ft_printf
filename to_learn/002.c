#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void print(char *placeholders, ...)
{
	int num_args = strlen(placeholders);

	va_list args;
	va_start(args, placeholders);
	int i = 0;
	while (i < num_args)
	{
		if (placeholders[i] == 'd')
		{
			int x = va_arg(args, int);
			printf("%d\n", x);
		}
		else if (placeholders[i] == 'f')
		{
			double x = va_arg(args, double);
			printf("%f\n", x);
		}
		i++;
	}
	va_end(args);
}

int main(void)
{
	print("fdfd", 1.2, 2, 5.3, 2);
}