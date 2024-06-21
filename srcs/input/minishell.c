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

int	g_signals = 0;

int	ft_streq(const char *line, const char *s)
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

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sigact;
	char				*line;
	t_data				data;
	t_env				*our_env;

	(void)argv;
	if (argc != 1)
		return (perror("Usage: ./minishell\n"), 1);
	update_sig_handler(&sigact, SIG_HANDLE_IDLE);
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
		parse_and_exec(line, &data, &sigact);
		free(line);
	}
	return (0);
}
