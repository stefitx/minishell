/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:10:57 by atudor            #+#    #+#             */
/*   Updated: 2023/09/24 21:36:11 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		s_s1;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	s_s1 = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	while (s_s1 > i && ft_strchr(set, s1[s_s1 - 1]))
		s_s1--;
	res = malloc((s_s1 - i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < s_s1)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}
