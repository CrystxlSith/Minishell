/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:05:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/06/07 17:15:47 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_pars(const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += print_char(va_arg(args, int));
	if (c == 's')
		count += print_str(va_arg(args, char *));
	if (c == 'd' || c == 'i')
		count += print_nb(va_arg(args, int));
	if (c == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), c);
	if (c == 'p')
		count += ft_print_ptr(va_arg(args, unsigned long int));
	if (c == '%')
		return (write(1, "%", 1));
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && *(s + 1) != '\0')
			i += print_pars(*(++s), args);
		else
			i += write(1, s, 1);
		s++;
	}
	va_end(args);
	return (i);
}
