/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:07:00 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 23:10:24 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_strings(const char *s, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != sep && (s[i + 1] == sep || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_err(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	j = 0;
	matrix = ft_malloc_err(sizeof(char *) * (count_strings(s, c) + 1));
	while (s[i])
	{
		if ((i > 0 && s[i] != c && s[i - 1] == c) || (i == 0 && s[0] != c))
			start = i;
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			matrix[j++] = ft_substr_err(s, start, (i - start + 1));
		i++;
	}
	matrix[j] = NULL;
	return (matrix);
}

/*int main()
{
	char **splitted;

	splitted = ft_split("hola que tal", ' ');
	if (!splitted)
		return NULL;
	
	int i;
	i = 0;
	while(splitted[i])
	{jjhyujkjgtftdrefsearsdfbm
		printf("%s\n", splitted[i]);
		i++;
	}
}*/
