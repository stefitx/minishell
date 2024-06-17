/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:44:12 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:30 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

t_env	*env_get_var(t_env *var, char *name)
{
	while (var)
	{
		if (!ft_strncmp(var->name, name, ft_strlen(name)))
			return (var);
		var = var->next;
	}
	return (NULL);
}
