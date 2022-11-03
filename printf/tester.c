int main(void)
{

	printf("");
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
	printf("\n=======================================================\n");

	printf("%s", (char *)NULL);
	printf("\n");
	ft_printf("%s", (char *)NULL);
	printf("\n=======================================================\n");

	printf("%s", "some string with %s hehe");
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
	printf("\n=======================================================\n");

}