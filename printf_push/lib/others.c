/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:44:11 by mhrima            #+#    #+#             */
/*   Updated: 2022/11/06 10:47:43 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strchr(char *str, char to_find)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == to_find)
			return (str + i);
		i++;
	}
	return (NULL);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	res;
	int	neg;

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

int	print_space(int *addSpace)
{
	int	i;

	i = 0;
	while ((*addSpace)-- > 0)
		i += ft_putchar(' ');
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
