/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:40:18 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/26 17:36:44 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

// Tokenizer
enum						e_token_types
{
	TOKEN_SPACE,
	TOKEN_TEXT,
	TOKEN_QUOTE,
	TOKEN_VARIABLE,
	TOKEN_REDIR,
	TOKEN_PIPE
};

enum						e_quote_status
{
	None,
	Single,
	Double
};

typedef struct s_token
{
	char					*content;
	enum e_token_types		token_type;
	enum e_quote_status		quote_status;
	struct s_token			*next;
}							t_token;

typedef struct s_tokenizer_data
{
	int						i;
	int						start;
	char					quote;
	t_token					*tokens;
}							t_tokenizer_data;

// Refiner
typedef struct s_str_node
{
	char					*str;
	struct s_str_node		*next;
}							t_str_node;

typedef struct s_text_token
{
	char					*original;
	char					*original_quoted;
	t_str_node				*expanded;
	int						in_quotes;
	struct s_text_token		*next;
}							t_text_token;

enum						e_redir_types
{
	Infile,
	Outfile,
	Heredoc,
	Append
};

typedef struct s_redir_token
{
	enum e_redir_types		redir_type;
	t_text_token			*text_token;
	struct s_redir_token	*next;
}							t_redir_token;

typedef struct s_pipe_token
{
	int						fd_in;
	int						fd_out;
	struct s_pipe_token		*next;
}							t_pipe_token;

enum						e_ref_token_types
{
	R_Text,
	R_Redir,
	R_Pipe
};

typedef struct s_ref_token
{
	enum e_ref_token_types	token_type;
	t_text_token			*text_token;
	t_redir_token			*redir_token;
	t_pipe_token			*pipe_token;
	struct s_ref_token		*next;
}							t_ref_token;

typedef struct s_refiner_data
{
	char					*og;
	char					*og_quoted;
	int						in_quotes;
	int						add_new;
	char					*expansion;
	t_str_node				*expanded;
	t_ref_token				*ref_tokens;
}							t_refiner_data;

// Command Builder
typedef struct s_single_cmd
{
	t_text_token			*args;
	t_redir_token			*redirs;
	struct s_single_cmd		*next;
}							t_single_cmd;

typedef struct s_command
{
	t_single_cmd			*cmd_list;
	t_pipe_token			*pipes;
	struct s_command		*next;
}							t_command;

typedef struct s_cmd_builder_data
{
	t_command				*cmd_set;
	t_text_token			*args;
	t_redir_token			*redirs;
	t_redir_token			*prev_redir;
}							t_cmd_builder_data;

// token_utils.c
t_token						*create_token(char *s, enum e_token_types type,
								char quote);
t_token						*find_last_token(t_token *head);
void						add_token(t_token **head, char *s,
								enum e_token_types type, char quote);
void						clear_token_list(t_token *head);

// ref_token_utils.c
t_ref_token					*create_ref_token(enum e_ref_token_types type,
								void *data);
t_ref_token					*find_last_ref_token(t_ref_token *head);
void						add_ref_token(t_ref_token **head,
								enum e_ref_token_types type, void *data);
void						clear_ref_token_list(t_ref_token *head);

// str_node_utils.c
t_str_node					*create_str_node(char *s);
t_str_node					*clone_str_node(t_str_node *node);
t_str_node					*find_last_str_node(t_str_node *head);
void						add_str_node(t_str_node **head, t_str_node *node);
void						clear_str_node_list(t_str_node *head);

// text_token_utils.c
t_text_token				*create_text_token(char *original,
								char *original_quoted, t_str_node *expanded,
								int in_quotes);
t_text_token				*clone_text_token(t_text_token *token);
t_text_token				*find_last_text_token(t_text_token *head);
void						add_text_token(t_text_token **head,
								t_text_token *new);
void						clear_text_token_list(t_text_token *head);

// redir_token_utils.c
t_redir_token				*create_redir_token(enum e_redir_types type,
								t_text_token *data);
t_redir_token				*clone_redir_token(t_redir_token *token);
t_redir_token				*find_last_redir_token(t_redir_token *head);
void						add_redir_token(t_redir_token **head,
								t_redir_token *new);
void						clear_redir_token_list(t_redir_token *head);

// single_command_utils.c
t_single_cmd				*create_single_cmd(t_text_token *args,
								t_redir_token *redirs);
t_single_cmd				*find_last_single_cmd(t_single_cmd *head);
void						add_single_cmd(t_single_cmd **head,
								t_text_token *args, t_redir_token *redirs);
void						clear_single_cmd_list(t_single_cmd *head);

void						ft_strappend(char **s, char *add);

char						**ft_split_str(char const *s, char *c);

t_token						*split_tokens(char *cmd);

t_ref_token					*refine_tokens(t_token *raw_tokens);

char						*get_env_wrapper(char *var);

t_command					*build_commands(t_ref_token *tokens);

#endif