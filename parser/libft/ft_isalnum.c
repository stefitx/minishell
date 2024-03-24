/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:37:52 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/20 18:05:43 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/*
#include <stdio.h>

int main(void)
{
    printf("----------------------\n");
    printf("> ft_isalnum\n");
    printf("> 'A': %d\n", ft_isalnum('A'));
    printf("> 'z': %d\n", ft_isalnum('z'));
    printf("> '0': %d\n", ft_isalnum('0'));
    printf("> '[': %d\n", ft_isalnum('['));
    printf("----------------------\n");
}
*/
