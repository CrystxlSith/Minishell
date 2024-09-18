/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:22:50 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:24:55 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_ad(unsigned long int n)
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

void	print_ptr_fd(int fd, unsigned long int i)
{
	if (i > 15)
	{
		print_ptr_fd(fd, i / 16);
		print_ptr_fd(fd, i % 16);
	}
	else
	{
		if (i < 10)
			print_char_fd(fd, i + '0');
		else
			print_char_fd(fd, i - 10 + 'a');
	}
}

int	ft_print_ptr_fd(int fd, unsigned long int i)
{
	int	len;

	len = 0;
	if (i == 0)
	{
		len += write (fd, "(nil)", 5);
		return (len);
	}
	len += write(fd, "0x", 2);
	print_ptr_fd(fd, i);
	len += len_ad(i);
	return (len);
}
