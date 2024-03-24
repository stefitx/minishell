/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:48:54 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/21 18:47:02 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *start, int data, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)start;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)data;
		i++;
	}
	return (start);
}
