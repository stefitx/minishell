/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:44:56 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:32:36 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*s;
	int				i;
	int				size;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	size = ft_size(n);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	if (n < 0)
		s[i++] = '-';
	i = size - 1;
	while (n)
	{
		if (n < 0)
			n *= -1;
		s[i--] = (n % 10) + '0';
		n = n / 10;
	}
	s[size] = '\0';
	return (s);
}
