/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refiner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:04:17 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/26 17:07:45 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



char	*get_env_wrapper(char *var)
{
    if (!var)
        return (NULL);
    if (ft_strncmp(var, "?", 2) == 0)
        return ("0");
    return (getenv(var));
}