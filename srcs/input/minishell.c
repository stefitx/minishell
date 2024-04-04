/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:05 by atudor            #+#    #+#             */
/*   Updated: 2024/04/04 19:21:03 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../parser/parser.h"

int	ft_strcmp(const char *line, const char *s)
{
	size_t	i;
	size_t	len_line;
	size_t	len_s;

	len_s = ft_strlen(s);
	len_line = ft_strlen(line);
	if (len_line != len_s)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != s[i])
			break ;
		i++;
	}
	if (i == len_s)
		return (1);
	else
		return (0);
}

/*
int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*cmd;
	char	**cmd1;
	char	*cmd2;

	// t_data	*data;
	cmd = "cd /Users/atudor/Desktop/gitminishell/srcs";
	cmd2 = "ls -la";
	(void)argv;
	if (argc != 1)
		return (write(2, "Usage: ./minishell\n", 20));
	// signal_handler();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || ft_strcmp(line, "exit"))
			return (write(1, "exit\n", 5), exit(0), 0);
		if (ft_strcmp(line, cmd))
		{
			cmd1 = ft_split(cmd, ' ');
			changedir(cmd1);
		}
		if (ft_strcmp(line, cmd2))
			exec_cmd(env, cmd2);
	}
	return (0);
}
*/

// if signal is ctrl-D, says exit and exits

static void	parse_cmd(char *s)
{
	t_command		*cmd;
	t_single_cmd	*cursor;
	char			*redirs[] = {"<", ">", "<<", ">>"};
	t_text_token	*cursor2;
	t_str_node		*cursor2_2;
	t_redir_token	*cursor3;
	t_pipe_token	*cursor4;

	cmd = parse_command(s);
	if (!cmd)
		return ;
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
				printf("  - Original: `%s`\n", cursor3->text_token->original);
				printf("  - Original (With Quotes): `%s`\n",
					cursor3->text_token->original_quoted);
				printf("  In Quotes? %s\n",
					cursor3->text_token->in_quotes ? "Yes" : "No");
				if (cursor3->text_token->expanded)
				{
					printf("  Expanded:\n");
					cursor2_2 = cursor3->text_token->expanded;
					while (cursor2_2)
					{
						printf("    - `%s`\n", cursor2_2->str);
						cursor2_2 = cursor2_2->next;
					}
				}
				else
					printf("  Expanded: (null)\n");
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
}

static void	sig_handler_idle(int signal)
{
	if (signal == SIGINT)
	{
		rl_newline(0, 0);
		rl_on_new_line();
		rl_replace_line(" ", 0);
		rl_redisplay();
	}
}

static void	sig_idle(struct sigaction *sigact)
{
	(*sigact).sa_handler = sig_handler_idle;
	sigemptyset(&(*sigact).sa_mask);
	(*sigact).sa_flags = 0;
	sigaction(SIGINT, sigact, NULL);
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sigact;
	char				*line;

	(void)argv;
	(void)env;
	if (argc != 1)
		return (perror("Usage: ./minishell\n"), 1);
	sig_idle(&sigact);
	while (1)
	{
		line = readline("shortking👑$ ");
		if (!line || ft_strcmp(line, "exit"))
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		if (line[0])
		{
			add_history(line);
			parse_cmd(line);
		}
		free(line);
	}
	return (0);
}
