/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:35 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 12:22:18 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	main_loop(t_ref_token *token, t_cmd_builder_data *data)
{
	if (token->token_type == REF_TOKEN_PIPE)
	{
		add_single_cmd(&data->cmd_set->cmd_list, data->args, data->redirs);
		add_pipe_token(&data->cmd_set->pipes,
			clone_pipe_token(token->pipe_token));
		data->args = NULL;
		data->redirs = NULL;
	}
	else if (token->token_type == REF_TOKEN_TEXT)
	{
		if (data->prev_redir)
			data->prev_redir->text_token = text_token_clone(token->text_token);
		else
			text_token_append(&data->args, text_token_clone(token->text_token));
	}
	else
	{
		data->prev_redir = redir_token_clone(token->redir_token);
		redir_token_append(&data->redirs, data->prev_redir);
	}
	if (token->token_type != REF_TOKEN_REDIR)
		data->prev_redir = NULL;
}

t_command	*build_commands(t_ref_token *tokens)
{
	t_cmd_builder_data	data;

	ft_bzero(&data, sizeof(t_cmd_builder_data));
	data.cmd_set = ft_calloc(1, sizeof(t_command));
	while (tokens)
	{
		main_loop(tokens, &data);
		tokens = tokens->next;
	}
	if (data.args || data.redirs)
		add_single_cmd(&data.cmd_set->cmd_list, data.args, data.redirs);
	return (data.cmd_set);
}

/*
int	main(int argn, char **args)
{
	t_command		*cmd;
	t_single_cmd	*cursor;
	char			*redirs[] = {"<", ">", "<<", ">>"};
	t_token			*raw_tokens;
	t_ref_token		*tokens;
	t_text_token	*cursor2;
	t_str_node		*cursor2_2;
	t_redir_token	*cursor3;
	t_pipe_token	*cursor4;

	if (argn != 2)
		return (1);
	raw_tokens = split_tokens(args[1]);
	tokens = refine_tokens(raw_tokens);
	cmd = build_commands(tokens);
	token_list_clear(raw_tokens);
	ref_token_list_clear(tokens);
	cursor = cmd->cmd_list;
	cursor4 = cmd->pipes;
	while (cursor)
	{
		if (cursor->args)
		{
			printf("Args: \n");
			cursor2 = cursor->args;
			while (cursor2)
			{
				printf("- Original: `%s`\n", cursor2->original);
				printf("- Original (With Quotes): `%s`\n",
					cursor2->original_quoted);
				printf("In Quotes? %s\n", cursor2->in_quotes ? "Yes" : "No");
				if (cursor2->expanded)
				{
					printf("Expanded:\n");
					cursor2_2 = cursor2->expanded;
					while (cursor2_2)
					{
						printf("  - `%s`\n", cursor2_2->str);
						cursor2_2 = cursor2_2->next;
					}
				}
				else
					printf("Expanded: (null)\n");
				cursor2 = cursor2->next;
			}
		}
		else
			printf("Args: (null)\n");
		if (cursor->redirs)
		{
			printf("Redirs: \n");
			cursor3 = cursor->redirs;
			while (cursor3)
			{
				printf("- %s %s\n", redirs[cursor3->redir_type],
					cursor3->text_token->original);
				cursor3 = cursor3->next;
			}
		}
		else
			printf("Redirs: (null)\n");
		if (cursor4)
		{
			printf("Pipe: %d -> %d\n", cursor4->fd_in, cursor4->fd_out);
			cursor4 = cursor4->next;
			if (cursor4)
				printf("\n");
		}
		cursor = cursor->next;
		if (cursor)
			printf("\n");
	}
	clear_single_cmd_list(cmd->cmd_list);
	clear_pipe_token_list(cmd->pipes);
	free(cmd);
	return (0);
}
*/