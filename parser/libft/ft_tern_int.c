/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tern_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:42:17 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/11 19:42:54 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tern_int(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}
