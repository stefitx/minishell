/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refiner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:22:04 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 11:58:03 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_special_token(t_token *raw_token, t_refiner_data *data);
static void	handle_text_token(t_token *raw_token, t_refiner_data *data);
static void	handle_var_token(t_token *raw_token, t_refiner_data *data);
static void	handle_unquoted_var(t_refiner_data *data);

t_ref_token	*refine_tokens(t_token *raw_tokens)
{
	t_refiner_data	data;

	ft_bzero(&data, sizeof(t_refiner_data));
	while (raw_tokens)
	{
		if (raw_tokens->token_type == TOKEN_TEXT
			|| raw_tokens->token_type == TOKEN_VARIABLE)
		{
			if (raw_tokens->quote_status != QUOTE_NONE)
				data.in_quotes = 1;
			if (raw_tokens->token_type == TOKEN_VARIABLE)
				handle_var_token(raw_tokens, &data);
			else
				handle_text_token(raw_tokens, &data);
		}
		else if (raw_tokens->token_type == TOKEN_QUOTE)
			ft_strappend(&data.og_quoted, raw_tokens->content);
		else
			handle_special_token(raw_tokens, &data);
		raw_tokens = raw_tokens->next;
	}
	if (data.og || data.og_quoted)
		add_ref_text_token(&data);
	return (data.ref_tokens);
}

static void	handle_special_token(t_token *raw_token, t_refiner_data *data)
{
	if ((data->og && data->og[0]) || data->in_quotes)
		add_ref_text_token(data);
	if (raw_token->token_type == TOKEN_REDIR)
		add_ref_redir_token(raw_token->content, data);
	else if (raw_token->token_type == TOKEN_PIPE)
		ref_token_append(&data->ref_tokens, REF_TOKEN_PIPE,
			create_pipe_token());
}

static void	handle_text_token(t_token *raw_token, t_refiner_data *data)
{
	ft_strappend(&data->og, raw_token->content);
	ft_strappend(&data->og_quoted, raw_token->content);
	if (data->add_new)
	{
		data->add_new = 0;
		add_str_node(&data->expanded, create_str_node(raw_token->content));
	}
	else
	{
		if (!data->expanded)
			add_str_node(&data->expanded, create_str_node(""));
		ft_strappend(&find_last_str_node(data->expanded)->str,
			raw_token->content);
	}
}

static void	handle_var_token(t_token *raw_token, t_refiner_data *data)
{
	ft_strappend(&data->og, "$");
	ft_strappend(&data->og, raw_token->content);
	ft_strappend(&data->og_quoted, "$");
	ft_strappend(&data->og_quoted, raw_token->content);
	data->expansion = get_env(raw_token->content);
	if (data->expansion)
	{
		if (raw_token->quote_status != QUOTE_NONE)
		{
			if (!data->expanded)
				add_str_node(&data->expanded, create_str_node(""));
			ft_strappend(&find_last_str_node(data->expanded)->str,
				get_env(raw_token->content));
		}
		else
			handle_unquoted_var(data);
		data->expansion = NULL;
	}
}

static void	handle_unquoted_var(t_refiner_data *data)
{
	char	**split_str;
	int		i;

	split_str = ft_split_set(data->expansion, get_ifs_set());
	i = 0;
	while (split_str[i])
	{
		if (i == 0 && (!data->expanded || !is_space_char(data->expansion[0])))
		{
			if (!data->expanded)
				add_str_node(&data->expanded, create_str_node(""));
			ft_strappend(&find_last_str_node(data->expanded)->str,
				split_str[i]);
		}
		else
			add_str_node(&data->expanded, create_str_node(split_str[i]));
		free(split_str[i++]);
	}
	free(split_str);
	data->add_new = data->expansion && ft_strchr(get_ifs_set(),
			data->expansion[ft_strlen(data->expansion) - 1]);
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
