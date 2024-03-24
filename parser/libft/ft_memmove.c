/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:58:41 by pfontenl          #+#    #+#             */
/*   Updated: 2023/11/08 18:38:55 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	if (!a && !b)
		return (NULL);
	if (a < b && (size_t)(b - a) < len)
	{
		i = len;
		while (i-- > 0)
			b[i] = a[i];
	}
	else
	{
		i = 0;
		while (i++ < len)
			b[i - 1] = a[i - 1];
	}
	return (dst);
}
