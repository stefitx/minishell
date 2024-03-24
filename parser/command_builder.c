#include "parser.h"

t_command   *build_commands(t_refined_token *tokens)
{
    t_command       *cmd_set;
    t_text_token    *args;
    t_redir_token   *redirs;
    t_redir_token   *prev_redir;

    cmd_set = ft_calloc(1, sizeof(t_command));
    args = NULL;
    redirs = NULL;
    prev_redir = NULL;
    while (tokens)
    {
        if (tokens->token_type == R_Pipe)
        {
            add_single_command(&cmd_set->cmd_list, args, redirs);
            args = NULL;
            redirs = NULL;
        }
        else if (tokens->token_type == R_Text)
        {
            if (prev_redir)
                prev_redir->text_token = clone_text_token(tokens->text_token);
            else
                add_text_token(&args, clone_text_token(tokens->text_token));
        }
        else
        {
            prev_redir = clone_redir_token(tokens->redir_token);
            add_redir_token(&redirs, prev_redir);
        }
        if (tokens->token_type != R_Redir)
            prev_redir = NULL;
        tokens = tokens->next;
    }
    if (args || redirs)
        add_single_command(&(cmd_set->cmd_list), args, redirs);
    return (cmd_set);
}

int	main(int argn, char **args)
{
	t_command           *cmd;
    t_single_command    *cursor;
	char	*redirs[] = {"<", ">", "<<", ">>"};

	if (argn != 2)
		return (1);
	t_token *raw_tokens = SplitTokens(args[1]);
	t_refined_token *tokens = RefineTokens(raw_tokens);
    cmd = build_commands(tokens);
    cursor = cmd->cmd_list;
	while (cursor)
	{
		if (cursor->args)
        {
            printf("Args: \n");
            t_text_token *cursor2 = cursor->args;
            while (cursor2)
            {
                printf("- `%s`\n", cursor2->original);
                cursor2 = cursor2->next;
            }
        }
        else
            printf("Args: (null)\n");
        if (cursor->redirs)
        {
            printf("Redirs: \n");
            t_redir_token *cursor2 = cursor->redirs;
            while (cursor2)
            {
                printf("- %s %s\n", redirs[cursor2->redir_type], cursor2->text_token->original);
                cursor2 = cursor2->next;
            }
        }
        else
            printf("Redirs: (null)\n");
		cursor = cursor->next;
        if (cursor)
            printf("\n");
	}
	return (0);
}