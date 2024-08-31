/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crystal <crystal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:36:23 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/07/20 21:06:10 by crystal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hex_len(unsigned int n)
{
	int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 16;
	}
	return (i);
}

void	print(unsigned int i, const char c)
{
	if (i > 15)
	{
		print(i / 16, c);
		print(i % 16, c);
	}
	else
	{
		if (i < 10)
			print_nb(i);
		else
		{
			if (c == 'x')
				print_char(i - 10 + 'a');
			if (c == 'X')
				print_char(i - 10 + 'A');
		}
	}
}

int	ft_print_hex(unsigned int i, char c)
{
	if (i == 0)
		return (write(1, "0", 1));
	else
		print(i, c);
	return (hex_len(i));
}
