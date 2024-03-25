/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refiner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:22:04 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/25 12:29:17 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*GetEnv(char *_var);

static void	handle_special_token(t_token *raw_token, t_refiner_data *data)
{
	enum e_redir_types	redirType;

	if ((data->og && data->og[0]) || data->in_quotes)
	{
		add_ref_token(&data->ref_tokens, R_Text, create_text_token(data->og,
				data->og_quoted, data->expanded, data->in_quotes));
		data->og = NULL;
		data->og_quoted = NULL;
		data->expanded = NULL; // Create Clear Func
		data->in_quotes = 0;
	}
	if (raw_token->token_type == TOKEN_REDIR)
	{
		redirType = Infile;
		if (ft_strncmp(raw_token->content, ">", 2) == 0)
			redirType = Outfile;
		else if (ft_strncmp(raw_token->content, "<<", 3) == 0)
			redirType = Heredoc;
		else if (ft_strncmp(raw_token->content, ">>", 3) == 0)
			redirType = Append;
		add_ref_token(&data->ref_tokens, R_Redir, create_redir_token(redirType,
				NULL));
	}
	else if (raw_token->token_type == TOKEN_PIPE)
		add_ref_token(&data->ref_tokens, R_Pipe, NULL);
}

static void	handle_var_token(t_token *raw_token, t_refiner_data *data)
{
	char	**splitNodes;
	int		i;

	ft_strappend(&data->og, "$");
	ft_strappend(&data->og, raw_token->content);
	ft_strappend(&data->og_quoted, "$");
	ft_strappend(&data->og_quoted, raw_token->content);
	data->expansion = GetEnv(raw_token->content);
	if (data->expansion)
	{
		if (raw_token->quote_status != None)
		{
			if (!data->expanded)
				add_str_node(&data->expanded, create_str_node(""));
			ft_strappend(&find_last_str_node(data->expanded)->str,
				GetEnv(raw_token->content));
		}
		else
		{
			splitNodes = ft_split_str(data->expansion, " \t\n");
			i = 0;
			while (splitNodes[i])
			{
				if (i == 0 && (!data->expanded || !ft_strchr(" \t\n",
							data->expansion[0])))
				{
					if (!data->expanded)
						add_str_node(&data->expanded, create_str_node(""));
					ft_strappend(&find_last_str_node(data->expanded)->str,
						splitNodes[i]);
				}
				else
					add_str_node(&data->expanded,
						create_str_node(splitNodes[i]));
				free(splitNodes[i++]);
			}
			data->add_new = data->expansion && ft_strchr(" \t\n",
					data->expansion[ft_strlen(data->expansion) - 1]);
		}
	}
}

t_ref_token	*refine_tokens(t_token *raw_tokens)
{
	t_refiner_data	data;

	ft_bzero(&data, sizeof(t_refiner_data));
	while (raw_tokens)
	{
		if (raw_tokens->token_type == TOKEN_SPACE
			|| raw_tokens->token_type == TOKEN_REDIR
			|| raw_tokens->token_type == TOKEN_PIPE)
			handle_special_token(raw_tokens, &data);
		else if (raw_tokens->token_type == TOKEN_QUOTE)
			ft_strappend(&data.og_quoted, raw_tokens->content);
		else
		{
			if (raw_tokens->quote_status != None)
				data.in_quotes = 1;
			if (raw_tokens->token_type == TOKEN_VARIABLE)
				handle_var_token(raw_tokens, &data);
			else
			{
				ft_strappend(&data.og, raw_tokens->content);
				ft_strappend(&data.og_quoted, raw_tokens->content);
				if (data.add_new)
				{
					data.add_new = 0;
					add_str_node(&data.expanded,
						create_str_node(raw_tokens->content));
				}
				else
				{
					if (!data.expanded)
						add_str_node(&data.expanded, create_str_node(""));
					ft_strappend(&find_last_str_node(data.expanded)->str,
						raw_tokens->content);
				}
			}
		}
		raw_tokens = raw_tokens->next;
	}
	if (data.og || data.og_quoted)
		add_ref_token(&data.ref_tokens, R_Text, create_text_token(data.og,
				data.og_quoted, data.expanded, data.in_quotes));
	return (data.ref_tokens);
}

// Mock-Up Of getenv() Function
static char	*GetEnv(char *_var)
{
	return (getenv(_var));
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

/*
int	main(int argn, char **args)
{
	t_ref_token	*tokens;
	char		*types[] = {"Text", "Redir", "Pipe"};
	t_token		*raw_tokens;
	int			i;
	t_str_node	*cursor;

	char		*redirs[] = {"Infile (<)", "Outfile (>)", "Heredoc (<<)",
				"Append (>>)"};
	if (argn != 2)
		return (1);
	raw_tokens = SplitTokens(args[1]);
	tokens = RefineTokens(raw_tokens);
	while (tokens)
	{
		printf("Type: %s\n", types[tokens->token_type]);
		printf("%p, %p, %p\n", tokens->text_token, tokens->redir_token,
			tokens->pipe_token);
		if (tokens->token_type == R_Text)
		{
			printf("data.og: %s\n", tokens->text_token->data.og);
			printf("data.og (Quoted): %s\n",
				tokens->text_token->data.og_quoted);
			if (tokens->text_token->data.expanded)
			{
				printf("data.expanded: \n");
				i = 0;
				cursor = tokens->text_token->data.expanded;
				while (cursor)
				{
					printf("- `%s`\n", cursor->str);
					cursor = cursor->next;
				}
			}
			else
				printf("data.expanded: (null)\n");
			printf("In Quotes?: %s\n",
				tokens->text_token->in_quotes ? "Yes" : "No");
		}
		if (tokens->token_type == R_Redir)
			printf("Redirection: %s\n",
				redirs[tokens->redir_token->redir_type]);
		tokens = tokens->next;
	}
	return (0);
}
*/
