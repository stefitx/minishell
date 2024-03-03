/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:53:51 by atudor            #+#    #+#             */
/*   Updated: 2023/09/19 13:05:52 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}
/*int main(void)
{
	char *b;
	int	i;
	

	i = 0;
	b = malloc(sizeof(char) *40);
	ft_bzero(b, 4);
	b[4] = 'b';
	while (b[i] == '\0')
	{
		printf("There is a  \\0 in position %d\n", i);
		i++;
	}
	printf("and in %d i have my b\n", i);
	return 0;
}*/
