/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 11:42:36 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_init(t_env **env, char **og_env)
{
	int		i;
	char	*name;
	char	*val;

	while (*og_env)
	{
		i = 0;
		while ((*og_env)[i] != '=')
			i++;
		name = ft_substr(*og_env, 0, i);
		val = ft_substr(*og_env, i + 1, ft_strlen(*og_env));
		env_add_var(env, name, val);
		og_env++;
	}
	env_add_var(env, ft_strdup("?"), ft_strdup("0"));
}