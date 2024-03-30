/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:45:06 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 11:45:14 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_set_var(t_env **env, char *name, char *val)
{
	t_env	*var;

	var = env_get_var(*env, name);
	if (!var)
		env_add_var(env, name, val);
	else
	{
		free(var->val);
		var->val = val;
	}
}
