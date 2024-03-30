/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:48 by atudor            #+#    #+#             */
/*   Updated: 2023/09/30 00:02:51 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr1;

	i = 0;
	if (!dst && !src)
		return (NULL);
	ptr = dst;
	ptr1 = src;
	while (i < n)
	{
		ptr[i] = ptr1[i];
		i++;
	}
	return (dst);
}

/*int	main(void)
{
	//char *dst = "ddddd";
	char *src = "yaaaaaas";
	char *dst = malloc(10 * sizeof(char));
	printf("%s", ft_memcpy(dst, src, 3));
			return 0;
			}*/
