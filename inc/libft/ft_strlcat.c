/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:41:35 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:04:00 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_src;
	size_t	s_dst;
	size_t	i;

	i = 0;
	s_dst = 0;
	s_src = 0;
	while (dst[s_dst] != '\0')
		s_dst++;
	while (src[s_src] != '\0')
		s_src++;
	if (s_dst > dstsize)
		return (s_src + dstsize);
	while (src[i] && i + s_dst + 1 < dstsize)
	{
		dst[s_dst + i] = src[i];
		i++;
	}
	dst[s_dst + i] = '\0';
	return (s_dst + s_src);
}
/*
int	main(void)
{
	char hehe[20] = "hello";
	char uh[20] = "world";
	char hehe2[20] = "hello";
	char uh2[20] = "world";
	//hehe = malloc(20 * sizeof(char));
	printf("ft %zu\n", ft_strlcat(hehe, uh, 5));
	printf("good %zu\n", strlcat(hehe2, uh2, 5));
	printf("good %s\n", hehe2);
	printf("ft %s\n", hehe);
	return 0;
}*/
