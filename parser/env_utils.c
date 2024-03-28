/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:40:03 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/28 12:46:44 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void	env_test(char **env)
{
	int		i;
	char	*name;
	char	*val;

	printf("[ ENV TEST ]\n\n");
	while (*env)
	{
		i = 0;
		while ((*env)[i] != '=')
			i++;
		name = ft_substr(*env, 0, i);
		val = ft_substr(*env, i + 1, ft_strlen(*env));
		printf("Name: %s\nValue: %s\n\n", name, val);
		env++;
	}
}

int	main(int argn, char **args, char **env)
{
	env_test(env);
	return (0);
}
