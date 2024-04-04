/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:28:45 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/04 19:21:08 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_quote(char *cmd, t_tokenizer_data *data)
{
	if (data->quote == cmd[data->i])
		data->quote = '\0';
	else
		data->quote = cmd[data->i];
	token_append(&data->tokens, ft_substr(cmd, data->i++, 1), TOKEN_QUOTE,
		data->quote);
}

static void	handle_control_char(char *cmd, t_tokenizer_data *data)
{
	if (ft_strchr("\"'", cmd[data->i]))
		handle_quote(cmd, data);
	else if (cmd[data->i] == '$' && data->quote != '\'')
	{
		data->start = ++data->i;
		while (cmd[data->i] && (ft_isalnum(cmd[data->i]) || cmd[data->i] == '_'
				|| (cmd[data->i] == '?' && data->start == data->i)))
			data->i++;
		if (data->i == data->start)
			token_append(&data->tokens, ft_strdup("$"), TOKEN_TEXT,
				data->quote);
		else
			token_append(&data->tokens, ft_substr(cmd, data->start, data->i
					- data->start), TOKEN_VARIABLE, data->quote);
	}
	else if (data->quote == '\0')
	{
		data->start = data->i;
		if (ft_strchr("<>", cmd[data->i]) && cmd[data->i] == cmd[data->i + 1])
			data->i++;
		token_append(&data->tokens, ft_substr(cmd, data->start, ++data->i
				- data->start), TOKEN_REDIR, data->quote);
	}
}

t_token	*split_tokens(char *cmd)
{
	t_tokenizer_data	data;

	ft_bzero(&data, sizeof(t_tokenizer_data));
	while (cmd[data.i])
	{
		data.start = data.i;
		while (cmd[data.i] && is_space_char(cmd[data.i]) && data.quote == '\0')
			data.i++;
		if (data.i > data.start)
			token_append(&data.tokens, NULL, TOKEN_SPACE, data.quote);
		data.start = data.i;
		while (cmd[data.i] && !is_control_char(cmd[data.i], data.quote))
			data.i++;
		if (data.i > data.start || data.quote != '\0')
			token_append(&data.tokens, ft_substr(cmd, data.start, data.i
					- data.start), TOKEN_TEXT, data.quote);
		if (cmd[data.i] && ft_strchr("$<>|\"'", cmd[data.i]))
			handle_control_char(cmd, &data);
	}
	return (data.tokens);
}

static int	syntax_check_loop(t_token *tokens, enum e_token_types *last_token,
		int *open_quotes)
{
	if (tokens->token_type == TOKEN_QUOTE)
		*open_quotes = !*open_quotes;
	if (tokens->token_type == TOKEN_PIPE)
	{
		if (*last_token == TOKEN_SPACE)
			return (write(STDERR_FILENO,
					"Syntax Error: Pipe At Start Of Command\n", 40), 1);
		if (*last_token == TOKEN_PIPE)
			return (write(STDERR_FILENO,
					"Syntax Error: Empty Space Between Pipes\n", 41), 1);
		if (*last_token == TOKEN_REDIR)
			return (write(STDERR_FILENO,
					"Syntax Error: Unfinished Redirection\n", 38), 1);
	}
	if (tokens->token_type == TOKEN_REDIR && (*last_token == TOKEN_REDIR
			|| *last_token == TOKEN_PIPE))
		return (write(STDERR_FILENO,
				"Syntax Error: Unfinished Redirection\n", 38), 1);
	if (tokens->token_type != TOKEN_SPACE)
		*last_token = tokens->token_type;
	return (0);
}

int	syntax_check(t_token *tokens)
{
	enum e_token_types	last_token;
	int					open_quotes;

	last_token = TOKEN_SPACE;
	open_quotes = 0;
	while (tokens)
	{
		if (syntax_check_loop(tokens, &last_token, &open_quotes))
			return (1);
		tokens = tokens->next;
	}
	if (open_quotes)
		return (write(STDERR_FILENO, "Syntax Error: Unclosed Quotes\n", 31), 1);
	if (last_token == TOKEN_REDIR)
		return (write(STDERR_FILENO, "Syntax Error: Unfinished Redirection\n",
				38), 1);
	if (last_token == TOKEN_PIPE)
		return (write(STDERR_FILENO, "Syntax Error: Pipe At End Of Command\n",
				38), 1);
	return (0);
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
