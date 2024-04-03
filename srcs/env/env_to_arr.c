/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:46:13 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 11:56:11 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_to_arr(t_env *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = ft_calloc(env_len(env) + 1, sizeof(char *));
	while (env)
	{
		ft_strappend(&env_arr[i], env->name);
		ft_strappend(&env_arr[i], "=");
		ft_strappend(&env_arr[i], env->val);
		env = env->next;
		i++;
	}
	return (env_arr);
}