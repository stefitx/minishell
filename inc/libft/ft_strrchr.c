/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:45:48 by atudor            #+#    #+#             */
/*   Updated: 2023/09/19 13:20:50 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (s[i] != (char)c)
	{
		if (i <= 0)
			return (NULL);
		else
			i--;
	}
	return ((char *)&s[i]);
}

/*int main(void)
{
	const char *s = "when will this pain end";
	int c = '\0';
	printf("this what the original outputs: %s", strrchr(s, c));
	printf("\nthis is mine: %s", ft_strrchr(s, c));
	return 0;
}*/
