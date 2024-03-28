/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:40:03 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/28 18:20:04 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "parser.h"

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
	env_add_var(env, ft_strdup("?"), ft_strdup("0"));
}

size_t	env_len(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

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

void	env_unset_var(t_env **env, char *name)
{
	t_env	*cursor;
	t_env	*prev;

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

void	env_clear_var(t_env *env_var)
{
	free(env_var->name);
	free(env_var->val);
}

void	env_clear_all(t_env *env)
{
	if (!env)
		return ;
	env_clear_var(env);
	env_clear_all(env->next);
	free(env->next);
}

char	**env_to_arr(t_env *env)
{
	int		i;
	char	**env_arr;

	i = 0;
	env_arr = ft_calloc(env_len(env) + 1, sizeof(char *));
	while (env)
	{
		ft_strappend(&env_arr[i], env->name);
		ft_strappend(&env_arr[i], "=");
		ft_strappend(&env_arr[i], env->val);
		env = env->next;
		i++;
	}
	return (env_arr);
}

void	env_test(char **env)
{
	t_env	*env_list;
	t_env	*cursor;
	char	**env_2;
	int		i;

	env_list = NULL;
	printf("[ ENV TEST ]\n\n");
	env_init(&env_list, env);
	env_set_var(&env_list, ft_strdup("a"), ft_strdup("aaaaaaaafmmsklfnasklgnkasgnk"));
	cursor = env_list;
	while (cursor)
	{
		printf("Name: %s\nValue: %s\n\n", cursor->name, cursor->val);
		cursor = cursor->next;
	}
	env_unset_var(&env_list, "a");
	env_2 = env_to_arr(env_list);
	env_clear_all(env_list);
	free(env_list);
	i = 0;
	while (env_2[i])
	{
		printf("%s\n", env_2[i]);
		free(env_2[i]);
		i++;
	}
	free(env_2);
}

int	main(int argn, char **args, char **env)
{
	env_test(env);
	return (0);
}
