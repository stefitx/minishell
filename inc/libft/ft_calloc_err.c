/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:01:55 by atudor            #+#    #+#             */
/*   Updated: 2023/09/13 21:02:44 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_err(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc_err(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}
