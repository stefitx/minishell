/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:10 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

void if_no_env(t_env **env)
{
	t_env	*cursor;
	int		val;


	cursor = env_get_var(*env, "SHLVL");
	if (cursor)
	{
		val = ft_atoi(cursor->val) + 1;
		if (val >= 1000)
			env_set_var(env, "SHLVL", ft_strdup(""));
		else
			env_set_var(env, "SHLVL", ft_strdup(ft_itoa(val)));
	}
	else
		env_add_var(env, ft_strdup("SHLVL"), ft_strdup("1"));
	env_set_var(env, ft_strdup("PWD"), getcwd(NULL, 0));
}

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
	if_no_env(env);
	env_add_var(env, ft_strdup("?"), ft_strdup("0"));
	env_add_var(env, ft_strdup("IFS"), NULL);
	if (getenv("IFS"))
		env_set_var(env, "IFS", ft_strdup(getenv("IFS")));
	
}
