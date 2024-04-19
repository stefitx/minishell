/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:45:18 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:16 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

void	env_unset_var(t_env **env, char *name)
{
	t_env	*cursor;
	t_env	*prev;

	if (ft_strncmp(name, "?", 2) == 0)
	{
		env_set_var(env, "?", ft_strdup("0"));
		return ;
	}
	cursor = *env;
	prev = NULL;
	while (cursor && ft_strncmp(cursor->name, name, ft_strlen(name)))
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (!cursor)
		return ;
	if (prev)
		prev->next = cursor->next;
	else
		*env = cursor->next;
	env_clear_var(cursor);
	free(cursor);
}
