/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refiner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:17:29 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:36:50 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	add_ref_text_token(t_refiner_data *data)
{
	ref_token_append(&data->ref_tokens, REF_TOKEN_TEXT,
		text_token_create(data->og, data->og_quoted, data->expanded,
			data->in_quotes));
	free(data->og);
	data->og = NULL;
	free(data->og_quoted);
	data->og_quoted = NULL;
	data->expanded = NULL;
	data->in_quotes = 0;
}

void	add_ref_redir_token(char *content, t_refiner_data *data)
{
	enum e_redir_types	redir_type;

	redir_type = REDIR_INFILE;
	if (ft_strncmp(content, ">", 2) == 0)
		redir_type = REDIR_OUTFILE;
	else if (ft_strncmp(content, "<<", 3) == 0)
		redir_type = REDIR_HEREDOC;
	else if (ft_strncmp(content, ">>", 3) == 0)
		redir_type = REDIR_APPEND;
	ref_token_append(&data->ref_tokens, REF_TOKEN_REDIR,
		redir_token_create(redir_type, NULL));
}
