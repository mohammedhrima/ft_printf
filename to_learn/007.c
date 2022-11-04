#include <stdio.h>
#include <stdarg.h>
#include <stdarg.h>

/* valist va_start, va_arg, va_end */
int add(int n, ...)
{
	va_list list;
	int sum = 0;
	int i = 0;

	//intiallize the list
	va_start(list,n);
	int i = 0;
	while (i < n)
		sum += va_arg(list, int); //every time I call va_arg it goes to the next element
	//close the list
	va_end(list);//free object
	return(sum);
}

int main(void)
{
	printf("-> %d\n", add(4/*4 arguments*/,4,12,25,32,12));
	printf("-> %d\n", add(4/*4 arguments*/,2,32,12));


}