#include "parser.h"

t_single_cmd	*create_single_cmd(t_text_token *args, t_redir_token *redirs)
{
	t_single_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_single_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
}

t_single_cmd	*find_last_single_cmd(t_single_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_single_cmd(t_single_cmd **head, t_text_token *args, t_redir_token *redirs)
{
	t_single_cmd	*new;

	new = create_single_cmd(args, redirs);
	if (!*head)
		*head = new;
	else
		find_last_single_cmd(*head)->next = new;
}
