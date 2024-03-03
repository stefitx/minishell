/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:34:10 by atudor            #+#    #+#             */
/*   Updated: 2023/09/07 15:39:44 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 2)
		printf("%d", ft_isdigit(argv[i][0]));
	return (0);
}*/
