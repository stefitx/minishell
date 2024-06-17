/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:45:41 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:32 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

void	env_clear_var(t_env *env_var)
{
	free(env_var->name);
	free(env_var->val);
}
