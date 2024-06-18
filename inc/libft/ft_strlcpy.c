/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:45 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:18:54 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	strlength;
	size_t	i;

	i = 0;
	while (dstsize > 0 && src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	strlength = 0;
	while (src[strlength] != '\0')
		strlength++;
	return (strlength);
}

/*int main(void)
{
char *dst = "yaaaaaa";
char *src = "nahhhhhhhh";
dst = malloc( 40 * sizeof(char));
printf("%zu", ft_strlcpy(dst, src, 5));
printf("%zu", strlcpy(dst, src, 5));
free(dst);
		return 0;
		}*/
