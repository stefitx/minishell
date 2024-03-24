/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:53:26 by pfontenl          #+#    #+#             */
/*   Updated: 2023/11/08 18:38:39 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (*s && s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			n++;
		i++;
	}
	return (n);
}

static char	*copy_word(char const *s, char c, size_t *cursor)
{
	size_t	start;
	size_t	len;

	while (s[*cursor] == c)
		(*cursor)++;
	start = *cursor;
	len = 0;
	while (s[*cursor] && s[*cursor] != c)
	{
		len++;
		(*cursor)++;
	}
	return (ft_substr(s, start, len));
}

static void	free_words(char **words, size_t word_count)
{
	size_t	i;

	i = 0;
	while (i < word_count)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	**split_words(char const *s, char c, size_t word_count)
{
	size_t	i;
	char	**words;
	size_t	cursor;

	words = ft_calloc(word_count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	cursor = 0;
	while (i < word_count)
	{
		words[i] = copy_word(s, c, &cursor);
		if (!words[i])
		{
			free_words(words, word_count);
			return (NULL);
		}
		i++;
	}
	words[i] = 0;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**words;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	words = split_words(s, c, word_count);
	return (words);
}
