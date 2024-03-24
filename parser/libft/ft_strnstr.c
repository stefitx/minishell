/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:14:25 by pfontenl          #+#    #+#             */
/*   Updated: 2023/11/08 18:40:06 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*to_find))
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (j < len - i && str[i + j] && to_find[j]
			&& str[i + j] == to_find[j])
			j++;
		if (!to_find[j])
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int main(void)
{
    printf("----------------------\n");
    printf("> ft_strnstr\n");
    printf("> 'Hello, world!', 'ell', 13: '%s'\n",
	ft_strnstr("Hello, world!", "ell", 13));
    printf("> 'Hello, world!', 'ell', 2:  %s\n",
	ft_strnstr("Hello, world!", "ell", 2));
	printf("> 'Hello, world!', '',    5:  '%s'\n",
	ft_strnstr("Hello, world!", "", 5));
	printf("> '',              'ell', -1: %s\n",
	ft_strnstr("", "ell", -1));
    printf("----------------------\n");
}
*/

/*
char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!to_find || !(*to_find))
		return ((char *)str);
	i = 0;
	j = 0;
	while (str[i] && i < len)
	{
		if (str[i] == to_find[j])
		{
			j++;
			if (!to_find[j])
				return ((char *)str + i - j + 1);
		}
		else if (j > 0)
			j = 0;
		i++;
	}
	return (NULL);
}
*/
