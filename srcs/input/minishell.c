/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:05 by atudor            #+#    #+#             */
/*   Updated: 2024/02/01 13:49:09 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(const char *line, const char *s)
{
	size_t	i;
	size_t	len_line;
	size_t	len_s;

	len_s = ft_strlen(s);
	len_line = ft_strlen(line);
	if (len_line != len_s)
		return 0;
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
	char	*line;
	// t_data	*data;
	char *cmd = "cd /Users/atudor/Desktop/gitminishell/srcs";
	char	**cmd1;

	char *cmd2 = "cd /Users/atudor/Desktop/gitminishell/srcs"; 

	(void)argv;

	if (argc != 1)
		return (write(2, "Usage: ./minishell\n", 20));
	//signal_handler();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			return 0;
		if (ft_strcmp(line, "exit"))
			return(write(1, "exit\n", 5));
		if (ft_strcmp(line, cmd))
		{
			cmd1 = ft_split(cmd, ' ');
			changedir(cmd1);
		}
		if (ft_strcmp(line, cmd2))
			exec_cmd(env, cmd2);
		// if (lexer(line))
		// {
		// 	data = parser(line, envp);
		// 	return(execution(data, envp));
		// }
	}
	return (0);
}

//if signal is ctrl-D, says exit and exits
