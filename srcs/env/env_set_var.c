/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:45:06 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:24 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

void	env_set_var(t_env **env, char *name, char *val)
{
	t_env	*var;
	
	var = env_get_var(*env, name);
	if (!var)
		env_add_var(env, name, val);
	else
	{
		if (var && var->val != NULL && val != NULL)
		{
			free(var->val);
			var->val = val;
		}
	}
}
