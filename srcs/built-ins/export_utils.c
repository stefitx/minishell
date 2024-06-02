/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:25 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:09:26 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
# include "../exec/exec.h"

int	is_addition(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_invalid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '+'
		&& str[i] != '=')
			return (1);
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

int has_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
