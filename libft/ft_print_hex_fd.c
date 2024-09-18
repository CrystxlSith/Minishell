/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:36:23 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:23:51 by agiliber         ###   ########.fr       */
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

void	print_fd(int fd, unsigned int i, const char c)
{
	if (i > 15)
	{
		print_fd(fd, i / 16, c);
		print_fd(fd, i % 16, c);
	}
	else
	{
		if (i < 10)
			print_nb_fd(fd, i);
		else
		{
			if (c == 'x')
				print_char_fd(fd, i - 10 + 'a');
			if (c == 'X')
				print_char_fd(fd, i - 10 + 'A');
		}
	}
}

int	ft_print_hex_fd(int fd, unsigned int i, char c)
{
	if (i == 0)
		return (write(fd, "0", 1));
	else
		print_fd(fd, i, c);
	return (hex_len(i));
}
