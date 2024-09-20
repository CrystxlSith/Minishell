/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:05:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:26:39 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_pars(int fd, const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += print_char_fd(fd, va_arg(args, int));
	if (c == 's')
		count += print_str_fd(fd, va_arg(args, char *));
	if (c == 'd' || c == 'i')
		count += print_nb_fd(fd, va_arg(args, int));
	if (c == 'u')
		count += print_unsigned_fd(fd, va_arg(args, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_print_hex_fd(fd, va_arg(args, unsigned int), c);
	if (c == 'p')
		count += ft_print_ptr_fd(fd, va_arg(args, unsigned long int));
	if (c == '%')
		return (write(fd, "%", 1));
	return (count);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && *(s + 1) != '\0')
			i += print_pars(fd, *(++s), args);
		else
			i += write(fd, s, 1);
		s++;
	}
	va_end(args);
	return (i);
}
