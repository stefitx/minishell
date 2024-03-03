/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:29:28 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:30:25 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		a;
	const unsigned char	*x;

	a = (unsigned char)c;
	x = s;
	while (n > 0)
	{
		if (*x == a)
			return ((unsigned char *)x);
		x++;
		n--;
	}
	return (0);
}
