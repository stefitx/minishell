/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:46:42 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/23 18:57:45 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_empty(void)
{
	char	*str;

	str = ft_calloc(1, sizeof(char));
	if (str)
		str[0] = '\0';
	return (str);
}

static size_t	wrapper_strlen(char const *str)
{
	if (!str)
		return (0);
	return (ft_strlen(str));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*str;
	size_t	len;

	l1 = wrapper_strlen((const char *)s1);
	l2 = wrapper_strlen((const char *)s2);
	if (l1 == 0 || l2 == 0)
	{
		if (l1 == 0 && l2 == 0)
			return (create_empty());
		else if (l1 == 0)
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	len = l1 + l2 + 1;
	str = ft_calloc(len, sizeof(char));
	if (str)
	{
		ft_strlcpy(str, s1, l1 + 1);
		ft_strlcat(str, s2, len);
	}
	return (str);
}
