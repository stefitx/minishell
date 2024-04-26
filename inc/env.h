/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:39:26 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/26 13:11:35 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

void				env_init(t_env **env, char **og_env);
size_t				env_len(t_env *env);
int					env_valid_name(char *s);
int					env_valid_name_substr(char *s, unsigned int start,
						size_t len);
void				env_add_var(t_env **env, char *name, char *val);
t_env				*env_get_var(t_env *var, char *name);
void				env_set_var(t_env **env, char *name, char *val);
void				env_unset_var(t_env **env, char *name);
void				env_clear_var(t_env *env_var);
void				env_clear_all(t_env *env);
char				**env_to_arr(t_env *env);

// Should be moved to libft
void				ft_strappend(char **s, char *new);

#endif