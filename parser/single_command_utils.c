#include "parser.h"

t_single_command	*create_single_command(t_text_token *args, t_redir_token *redirs)
{
	t_single_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_single_command));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
}

t_single_command	*find_last_single_command(t_single_command *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_single_command(t_single_command **head, t_text_token *args, t_redir_token *redirs)
{
	t_single_command	*new;

	new = create_single_command(args, redirs);
	if (!*head)
		*head = new;
	else
		find_last_single_command(*head)->next = new;
}
