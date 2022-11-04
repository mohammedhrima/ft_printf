#include <stdio.h>

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

size_t	ft_strlcat(char *dst, char  *src, size_t size)
{
	size_t	j;
	size_t	len;

	j = 0;
	if (!size || size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	len = ft_strlen(dst);
	while (j < size - len - 1 && src[j] != '\0')
	{
		dst[len + j] = src[j];
		j++;
	}
	dst[len + j] = '\0';
	return (ft_strlen(src) + len);
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

int main(void)
{
	/*float x = 5.785121;
	float y = 9.125645;
	float z = 15.2323545;
	printf("-> %.2f\n", x);
	printf("-> %.1f\n", y);
	printf("-> %.4f\n", z);*/
	char *str = "abcdefgh";
	char res[3];
	ft_strlcpy(res, str, 3);
	printf("-> %s\n", res);
	return (0);
}