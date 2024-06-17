/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:53:26 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/28 18:19:29 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "../../inc/minishell.h"

static size_t	count_words(char const *s, char *set)
{
	size_t	n;
	size_t	i;

	if (!set || !set[0])
		return (1);
	n = 0;
	i = 0;
	while (s && s[i])
	{
		if (!ft_strchr(set, s[i]) && (i == 0 || ft_strchr(set, s[i - 1])))
			n++;
		i++;
	}
	return (n);
}

static char	*copy_word(char const *s, char *set, size_t *cursor)
{
	size_t	start;
	size_t	len;

	while (ft_strchr(set, s[*cursor]))
		(*cursor)++;
	start = *cursor;
	len = 0;
	while (s[*cursor] && !ft_strchr(set, s[*cursor]))
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

char	**split_words(char const *s, char *set, size_t word_count)
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
		words[i] = copy_word(s, set, &cursor);
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

char	**ft_split_set(char const *s, char *set)
{
	size_t	word_count;
	char	**words;

	if (!s)
		return (NULL);
	word_count = count_words(s, set);
	words = split_words(s, set, word_count);
	return (words);
}
