/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:35:28 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/24 12:27:43 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*
#include <stdio.h>

int main(void)
{
    printf("----------------------\n");
    printf("> ft_isalpha\n");
    printf("> 'A': %d\n", ft_isalpha('A'));
    printf("> 'z': %d\n", ft_isalpha('z'));
    printf("> '0': %d\n", ft_isalpha('0'));
    printf("> '\\0': %d\n", ft_isalpha('\0'));
    printf("----------------------\n");
}
*/