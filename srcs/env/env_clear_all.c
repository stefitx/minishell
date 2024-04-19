/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:45:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:30:37 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

void	env_clear_all(t_env *env)
{
	if (!env)
		return ;
	env_clear_var(env);
	env_clear_all(env->next);
	free(env->next);
}
