/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tern_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:44:36 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/11 19:45:12 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_tern_ptr(int condition, void *true_val, void *false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}
