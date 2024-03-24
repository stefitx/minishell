/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:28:12 by pfontenl          #+#    #+#             */
/*   Updated: 2023/09/24 13:31:55 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*str_cpy;
	size_t	len;

	len = ft_strlen(str) + 1;
	str_cpy = ft_calloc(len, sizeof(char));
	if (str_cpy)
		ft_strlcpy(str_cpy, str, len);
	return (str_cpy);
}
