/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:57:48 by atudor            #+#    #+#             */
/*   Updated: 2023/09/12 20:24:33 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr1;

	i = 0;
	ptr = (unsigned char *)dst;
	ptr1 = (unsigned char *)src;
	if (dst < src)
	{
		while (i < len)
		{
			ptr[i] = ptr1[i];
			i++;
		}
	}
	else if (src < dst)
	{
		while (len--)
			ptr[len] = ptr1[len];
	}
	return (dst);
}

/*int	main(void)
{
	char *d = "hehehehe";
	char *s = "yeah";
	d = malloc (4 * sizeof(char));
	printf("%s\n", ft_memmove(d, s, 4));
			printf("%s\n", memmove(d, s, 4));
			return 0;
}*/
