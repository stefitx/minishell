/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tern_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:44:01 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/11 19:44:10 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_tern_char(int condition, char true_val, char false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}
