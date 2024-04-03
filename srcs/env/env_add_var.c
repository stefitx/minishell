/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:41:04 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/30 11:41:24 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_add_var(t_env **env, char *name, char *val)
{
	t_env	*new;
	t_env	*cursor;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	new->name = name;
	new->val = val;
	new->next = NULL;
	if (*env)
	{
		cursor = *env;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
	else
		*env = new;
}