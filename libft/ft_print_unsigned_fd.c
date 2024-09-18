/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:17:36 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:25:38 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_unsigned_fd(int fd, unsigned int nb)
{
	char	*str;
	int		len;

	str = ft_uitoa(nb);
	len = print_str_fd(fd, str);
	free(str);
	return (len);
}
