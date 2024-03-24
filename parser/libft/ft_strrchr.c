/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:36:36 by pfontenl          #+#    #+#             */
/*   Updated: 2023/11/08 18:39:42 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, char c)
{
	char	*cursor;

	cursor = (char *)str + ft_strlen(str);
	while (cursor >= str)
	{
		if (*cursor == c)
			return (cursor);
		cursor--;
	}
	return (NULL);
}
