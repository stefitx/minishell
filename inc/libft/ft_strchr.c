/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:18:56 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:27:01 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		a;
	const char	*x;
	int			i;

	a = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == a)
		{
			x = &s[i];
			return ((char *)x);
		}
		i++;
	}
	if (a == '\0')
		return ((char *)&s[i]);
	return (0);
}

/*int main(void)
{
	const char *s = "when will this pain end";
	int c = 'p';
	printf("this what the original outputs: %s", strchr(s, c));
	printf("\nthis is mine: %s", ft_strchr(s, c));
	return 0;
}*/
