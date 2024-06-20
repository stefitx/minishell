/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:05 by atudor            #+#    #+#             */
/*   Updated: 2024/04/27 15:44:15 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int g_signals = 0;

int	ft_strcmp(const char *line, const char *s)
{
	size_t	i;
	size_t	len_line;
	size_t	len_s;

	if (!line || !s)
		return (-1);
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

static void	rl_blank_line(void)
{
	int		i;
	char	*temp;

	temp = ft_strdup_err(rl_line_buffer);
	i = 0;
	while (i++ < 2)
		ft_strappend(&temp, " ");
	rl_on_new_line();
	rl_replace_line(temp, 1);
	rl_redisplay();
	free(temp);
}

static void	sig_handler_idle(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		g_signals = signal;
		rl_blank_line();
		if (signal == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (ft_strlen(rl_line_buffer) <= 2)
			rl_replace_line("", 1);
	}
}

void	sig_idle(struct sigaction *sigact)
{
	(*sigact).sa_handler = sig_handler_idle;
	sigemptyset(&(*sigact).sa_mask);
	(*sigact).sa_flags = 0;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sigact;
	char				*line;
	t_data				data;
	t_env				*our_env;

	(void)argv;

	if (argc != 1)
		return (perror("Usage: ./minishell\n"), 1);
	sig_idle(&sigact);
	our_env = NULL;
	env_init(&our_env, env);
	data.env_list = our_env;
	while (1)
	{
		g_signals = 0;
		line = readline("shortking👑$ ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		parse_and_exec(line, &data);
		free(line);
	}
	return (0);
}
//parse_cmd(line, our_env);
/*
static void	parse_cmd(char *s, t_env *env)
{
	t_command		*cmd;
	t_single_cmd	*cursor;
	char			*redirs[] = {"<", ">", "<<", ">>"};
	t_text_token	*cursor2;
	t_str_node		*cursor2_2;
	t_redir_token	*cursor3;
	t_pipe_token	*cursor4;

	cmd = parse_command(s, env);
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
				printf("Expanded Full: %s\n", cursor2->expanded_full);
				printf("Expanded Joined: %s\n", cursor2->expanded_joined);
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
				printf("IN PARSE COMMAND %s\n", 
					cursor3->text_token->expanded->str);	
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
				printf("Expanded Full: %s\n",
					cursor3->text_token->expanded_full);
				printf("Expanded Joined: %s\n",
					cursor3->text_token->expanded_joined);
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
	clear_command(cmd);
}
*/