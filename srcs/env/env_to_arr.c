/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:46:13 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/26 12:58:20 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

char	**env_to_arr(t_env *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = ft_calloc(env_len(env), sizeof(char *));
	while (env->next)
	{
		if (ft_strncmp(env->name, "?", 2) != 0
			&& ft_strncmp(env->name, "IFS", 4) != 0)
		{
			ft_strappend(&env_arr[i], env->name);
			ft_strappend(&env_arr[i], "=");
			ft_strappend(&env_arr[i], env->val);
		}
		env = env->next;
		i++;
	}
	return (env_arr);
}
