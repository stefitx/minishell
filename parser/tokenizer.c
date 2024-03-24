/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:28:45 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 13:21:20 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	IsSpaceChar(char c)
{
	return (ft_strchr(" \t\n", c) != NULL);
}

static int	IsControlChar(char c)
{
	return (IsSpaceChar(c) || ft_strchr("$<>|\"'", c));
}

static int	aaaa(char c, char quote)
{
	if (quote == '\'')
		return (c == '\'');
	if (quote == '"')
		return (ft_strchr("\"$", c) != NULL);
	return (IsControlChar(c));
}

t_token	*SplitTokens(char *cmd)
{
	int		i;
	int		start;
	char	quote;
	t_token	*tokens;

	quote = '\0';
	i = 0;
	tokens = NULL;
	while (cmd[i])
	{
		start = i;
		while (cmd[i] && IsSpaceChar(cmd[i]) && quote == '\0')
			i++;
		if (i > start)
			add_token(&tokens, NULL, TOKEN_SPACE, quote);
		start = i;
		while (cmd[i] && !aaaa(cmd[i], quote))
			i++;
		if (i > start || quote != '\0')
			add_token(&tokens, ft_substr(cmd, start, i - start), TOKEN_TEXT,
				quote);
		if (cmd[i] && ft_strchr("$<>|\"'", cmd[i]))
		{
			if (ft_strchr("\"'", cmd[i]))
			{
				if (quote == cmd[i])
					quote = '\0';
				else
					quote = cmd[i];
				add_token(&tokens, ft_substr(cmd, i++, 1), TOKEN_QUOTE, quote);
			}
			else if (cmd[i] == '$' && quote != '\'')
			{
				start = ++i;
				while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'
						|| (cmd[i] == '?' && start == i)))
					i++;
				// if (i == start)
				// 	throw new Exception("Error: Variable With No Name Detected!");
				add_token(&tokens, ft_substr(cmd, start, i - start),
					TOKEN_VARIABLE, quote);
			}
			else if (quote == '\0')
			{
				start = i;
				if (cmd[i] && cmd[i + 1] && ft_strchr("<>", cmd[i])
					&& cmd[i] == cmd[i + 1])
					i++;
				add_token(&tokens, ft_substr(cmd, start, ++i - start),
					TOKEN_REDIR, quote);
			}
		}
	}
	// if (quote != '\0')
	// 	throw new Exception("Error: Open Quotes Detected!");
	return (tokens);
}

// public static void SyntaxCheck(LinkedList<Token> _tokenList)
// {
//     LinkedListNode<Token> cursor = _tokenList.First;
//     LinkedListNode<Token> prevToken = null;
//     while (cursor != null)
//     {
//         if (cursor.Value.tokenType != TokenTypes.Space)
//         {
//             if (cursor.Value.tokenType == TokenTypes.Pipe)
//             {
//                 if (prevToken == null)
//                     throw new Exception("Syntax Error: Pipe At Start Of Command!");
//                 else if (prevToken.Value.tokenType == TokenTypes.Pipe)
//                     throw new Exception("Syntax Error: Empty Command Between Pipes!");
//                 else if (prevToken.Value.tokenType == TokenTypes.Redir)
//                     throw new Exception("Syntax Error: Incomplete Redirection!");
//             }
//             else if (cursor.Value.tokenType == TokenTypes.Redir)
//             {
//                 if (prevToken.Value.tokenType == TokenTypes.Redir)
//                     throw new Exception("Syntax Error: Incomplete Redirection!");
//             }
//             prevToken = cursor;
//         }
//         cursor = cursor.Next;
//     }
//     if (prevToken != null)
//     {
//         if (prevToken.Value.tokenType == TokenTypes.Pipe)
//             throw new Exception("Syntax Error: Pipe At End Of Command!");
//         else if (prevToken.Value.tokenType == TokenTypes.Redir)
//             throw new Exception("Syntax Error: Incomplete Redirection At End Of Command!");
//     }
// }

// int	main(int argn, char **args)
// {
// 	t_token	*tokens;
// 	char	*types[] = {"Space", "Text", "Quote", "Variable", "Redir", "Pipe"};
// 	char	*quotes[] = {"None", "Single", "Double"};

// 	if (argn != 2)
// 		return (1);
// 	tokens = SplitTokens(args[1]);
// 	while (tokens)
// 	{
// 		printf("`%s` (Type: %s) (Quote: %s)\n", tokens->content,
// 			types[tokens->token_type], quotes[tokens->quote_status]);
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }
