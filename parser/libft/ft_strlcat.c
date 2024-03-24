/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:13:08 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/21 18:56:45 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t l)
{
	size_t	i;
	size_t	offset;

	i = 0;
	while (dst && dst[i])
		i++;
	if (i >= l)
		return (ft_strlen(src) + l);
	offset = i;
	while (src && src[i - offset] && i < l - 1)
	{
		dst[i] = src[i - offset];
		i++;
	}
	dst[i] = '\0';
	while (src[i - offset])
		i++;
	return (i);
}
