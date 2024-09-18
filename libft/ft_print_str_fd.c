/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:19:01 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:22:46 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_str_fd(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (print_str_fd(fd, "(null)"));
	while (str[i])
		i += print_char_fd(fd, (int)str[i]);
	return (i);
}
