/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refiner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:22:04 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 14:22:17 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*GetEnv(char *_var);

static int	IsSpaceChar(char c)
{
	return (ft_strchr(" \t\n", c) != NULL);
}

t_refined_token	*RefineTokens(t_token *raw_tokens)
{
    // Join In Single Struct
	char			*original;
	char			*originalQuoted;
	int				inQuotes;
	int				addNew;
	char			*expansion;
    t_str_node      *expanded;
	t_refined_token	*refinedTokens;

	original = NULL;
	originalQuoted = NULL;
	inQuotes = 0;
	addNew = 0;
    expansion = NULL;
	expanded = NULL;
    refinedTokens = NULL;
	while (raw_tokens)
	{
		if (raw_tokens->token_type == TOKEN_SPACE
			|| raw_tokens->token_type == TOKEN_REDIR
			|| raw_tokens->token_type == TOKEN_PIPE)
		{
			if ((original && original[0]) || inQuotes)
			{
                add_refined_token(&refinedTokens, R_Text, create_text_token(original, originalQuoted, expanded, inQuotes));
				original = NULL;
				originalQuoted = NULL;
				expanded = NULL; // Create Clear Func
				inQuotes = 0;
			}
			if (raw_tokens->token_type == TOKEN_REDIR)
			{
				enum e_redir_types redirType = Infile;
				if (ft_strncmp(raw_tokens->content, ">", 2) == 0)
					redirType = Outfile;
				else if (ft_strncmp(raw_tokens->content, "<<", 3) == 0)
					redirType = Heredoc;
				else if (ft_strncmp(raw_tokens->content, ">>", 3) == 0)
					redirType = Append;
                add_refined_token(&refinedTokens, R_Redir, create_redir_token(redirType, NULL));
			}
			else if (raw_tokens->token_type == TOKEN_PIPE)
				add_refined_token(&refinedTokens, R_Pipe, NULL);
		}
		else if (raw_tokens->token_type == TOKEN_QUOTE)
			ft_strappend(&originalQuoted, raw_tokens->content);
		else
		{
			if (raw_tokens->quote_status != None)
				inQuotes = 1;
			if (raw_tokens->token_type == TOKEN_VARIABLE)
			{
				ft_strappend(&original, "$");
				ft_strappend(&original, raw_tokens->content);
				ft_strappend(&originalQuoted, "$");
				ft_strappend(&originalQuoted, raw_tokens->content);
				expansion = GetEnv(raw_tokens->content);
				if (expansion)
				{
					if (raw_tokens->quote_status != None)
					{
						if (!expanded)
							add_str_node(&expanded, create_str_node(""));
						ft_strappend(&find_last_str_node(expanded)->str, GetEnv(raw_tokens->content));
					}
					else
					{
						char **splitNodes = ft_split_str(expansion, " \t\n");
						int i = 0;
						while (splitNodes[i])
						{
							if (i == 0 && (!expanded || !IsSpaceChar(expansion[0])))
							{
								if (!expanded)
									add_str_node(&expanded, create_str_node(""));
								ft_strappend(&find_last_str_node(expanded)->str, splitNodes[i]);
							}
							else
								add_str_node(&expanded, create_str_node(splitNodes[i]));
							i++;
						}
						addNew = expansion && IsSpaceChar(expansion[ft_strlen(expansion) - 1]);
					}
				}
			}
			else
			{
				ft_strappend(&original, raw_tokens->content);
				ft_strappend(&originalQuoted, raw_tokens->content);
				if (addNew)
				{
					addNew = 0;
                    add_str_node(&expanded, create_str_node(raw_tokens->content));
				}
				else
				{
					if (!expanded)
                        add_str_node(&expanded, create_str_node(""));
					ft_strappend(&find_last_str_node(expanded)->str, raw_tokens->content);
				}
			}
		}
		raw_tokens = raw_tokens->next;
	}
	if (original || originalQuoted)
		add_refined_token(&refinedTokens, R_Text, create_text_token(original, originalQuoted, expanded, inQuotes));
	return (refinedTokens);
}

// Mock-Up Of getenv() Function
static char	*GetEnv(char *_var)
{
	return getenv(_var);
	// switch (_var)
	// {
	// // case "a": return ("    1    2    ");
	// // case "b": return ("    3    4    ");
	// case "a":
	// 	return ("1");
	// case "b":
	// 	return ("");
	// case "n":
	// 	return ("");
	// case "no":
	// 	return (NULL);
	// default:
	// 	return ($ "<Value_Of_${_var}>");
	// }
}

// int	main(int argn, char **args)
// {
// 	t_refined_token	*tokens;
// 	char	*types[] = {"Text", "Redir", "Pipe"};
// 	char	*redirs[] = {"Infile (<)", "Outfile (>)", "Heredoc (<<)", "Append (>>)"};

// 	if (argn != 2)
// 		return (1);
// 	t_token *raw_tokens = SplitTokens(args[1]);
// 	tokens = RefineTokens(raw_tokens);
// 	while (tokens)
// 	{
// 		printf("Type: %s\n", types[tokens->token_type]);
// 		// printf("%p, %p, %p\n", tokens->text_token, tokens->redir_token, tokens->pipe_token);
// 		if (tokens->token_type == R_Text)
// 		{
// 			printf("Original: %s\n", tokens->text_token->original);
// 			printf("Original (Quoted): %s\n", tokens->text_token->original_quoted);
// 			if (tokens->text_token->expanded)
// 			{
// 				printf("Expanded: \n");
// 				int i = 0;
// 				t_str_node *cursor = tokens->text_token->expanded;
// 				while (cursor)
// 				{
// 					printf("- `%s`\n", cursor->str);
// 					cursor = cursor->next;
// 				}
// 			}
// 			else
// 				printf("Expanded: (null)\n");
// 			printf("In Quotes?: %s\n", tokens->text_token->in_quotes ? "Yes" : "No");
// 		}
// 		if (tokens->token_type == R_Redir)
// 			printf("Redirection: %s\n", redirs[tokens->redir_token->redir_type]);
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }
