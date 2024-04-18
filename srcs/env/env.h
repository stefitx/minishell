/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:39:26 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/18 18:27:02 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../inc/libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

void				env_add_var(t_env **env, char *name, char *val);
void				env_init(t_env **env, char **og_env);
size_t				env_len(t_env *env);
t_env				*env_get_var(t_env *var, char *name);
void				env_set_var(t_env **env, char *name, char *val);
void				env_unset_var(t_env **env, char *name);
void				env_clear_var(t_env *env_var);
void				env_clear_all(t_env *env);
char				**env_to_arr(t_env *env);

// Should be moved to libft
void				ft_strappend(char **s, char *new);

#endif