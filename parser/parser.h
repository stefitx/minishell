/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:40:18 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 14:14:26 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

// Tokenizer
enum							e_token_types
{
	TOKEN_SPACE,
	TOKEN_TEXT,
	TOKEN_QUOTE,
	TOKEN_VARIABLE,
	TOKEN_REDIR,
	TOKEN_PIPE
};

enum							e_quote_status
{
	None,
	Single,
	Double
};

typedef struct s_token
{
	char						*content;
	enum e_token_types			token_type;
	enum e_quote_status			quote_status;
	struct s_token				*next;
}								t_token;

// Refiner
typedef struct s_str_node
{
	char						*str;
	struct s_str_node			*next;
}								t_str_node;

typedef struct s_text_token
{
	char						*original;
	char						*original_quoted;
	t_str_node					*expanded;
	int							in_quotes;
	struct s_text_token			*next;
}								t_text_token;

enum							e_redir_types
{
	Infile,
	Outfile,
	Heredoc,
	Append
};

typedef struct s_redir_token
{
	enum e_redir_types			redir_type;
	t_text_token				*text_token;
	struct s_redir_token		*next;
}								t_redir_token;

typedef struct s_pipe_token
{
	int							fd_in;
	int							fd_out;
	struct s_pipe_token			*next;
}								t_pipe_token;

enum							e_refined_token_types
{
	R_Text,
	R_Redir,
	R_Pipe
};

typedef struct s_refined_token
{
	enum e_refined_token_types	token_type;
	t_text_token				*text_token;
	t_redir_token				*redir_token;
	t_pipe_token				*pipe_token;
	struct s_refined_token		*next;
}								t_refined_token;

// Command Builder
typedef struct s_single_command
{
	t_text_token				*args;
	t_redir_token				*redirs;
	struct s_single_command		*next;
}								t_single_command;

typedef struct s_command
{
	t_single_command		*cmd_list;
	t_pipe_token			*pipes;
	struct s_command		*next;
}              t_command;

// token_utils.c
t_token							*create_token(char *s, enum e_token_types type,
									char quote);
t_token							*find_last_token(t_token *head);
void							add_token(t_token **head, char *s,
									enum e_token_types type, char quote);

// refined_token_utils.c
t_refined_token					*create_refined_token(enum e_refined_token_types type,
									void *data);
t_refined_token					*find_last_refined_token(t_refined_token *head);
void							add_refined_token(t_refined_token **head,
									enum e_refined_token_types type,
									void *data);

// str_node_utils.c
t_str_node						*create_str_node(char *s);
t_str_node						*clone_str_node(t_str_node *node);
t_str_node						*find_last_str_node(t_str_node *head);
void							add_str_node(t_str_node **head, t_str_node *node);
void							clear_str_node_list(t_str_node *head);

// text_token_utils.c
t_text_token					*create_text_token(char *original,
									char *original_quoted, t_str_node *expanded,
									int in_quotes);
t_text_token					*clone_text_token(t_text_token *token);
t_text_token					*find_last_text_token(t_text_token *head);
void							add_text_token(t_text_token **head,
									t_text_token *new);
void							clear_text_token_list(t_text_token *head);

// redir_token_utils.c
t_redir_token					*create_redir_token(enum e_redir_types type,
									t_text_token *data);
t_redir_token					*clone_redir_token(t_redir_token *token);
t_redir_token					*find_last_redir_token(t_redir_token *head);
void							add_redir_token(t_redir_token **head, t_redir_token *new);
void							clear_redir_token_list(t_redir_token *head);

t_single_command	*create_single_command(t_text_token *args, t_redir_token *redirs);
t_single_command	*find_last_single_command(t_single_command *head);
void				add_single_command(t_single_command **head, t_text_token *args, t_redir_token *redirs);

void	ft_strappend(char **s, char *add);

char	**ft_split_str(char const *s, char *c);

t_token	*SplitTokens(char *cmd);

t_refined_token	*RefineTokens(t_token *raw_tokens);

t_command   *build_commands(t_refined_token *tokens);

#endif