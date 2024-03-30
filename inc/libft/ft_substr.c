/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:19:15 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:37:43 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*sub;

	if (!s || len == 0)
		return (ft_strdup(""));
	size = 0;
	while (s[size])
		size++;
	if (start >= size)
		return (ft_strdup(""));
	else if (size - start < len)
		sub = malloc((size - start + 1) * (sizeof(char)));
	else
		sub = malloc((len + 1) * (sizeof(char)));
	if (!sub)
		return (NULL);
	i = 0;
	len += start;
	while (s[start] && start < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

/*int	main(void)
{
	char s[] = "hey jude, don't be afraid";
	printf("%s", ft_substr(s, 3, 20));
			return 0;
			}*/
