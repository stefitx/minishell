/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:51:00 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/21 18:37:46 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *start, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)start;
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
#include <stdio.h>

int main(void)
{
    printf("-----------------------------------------\n");
    printf("> ft_bzero\n");
    printf("> '0':                     %d\n",
	ft_atoi("0"));
	printf("\n");
    printf("-----------------------------------------\n");
}
*/