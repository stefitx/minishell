/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:44:51 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:13:33 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	x;
	char	*p;

	i = 0;
	j = ft_strlen(needle);
	p = (char *)haystack;
	if (needle[0] == '\0')
		return (p);
	while (p[i] != 0 && i < len)
	{
		if (p[i] == needle[0])
		{
			x = 0;
			while (p[i + x] == needle[x] && (i + x) < len)
			{
				x++;
				if (x == j)
					return (&p[i]);
			}
		}
		i++;
	}
	return (NULL);
}
