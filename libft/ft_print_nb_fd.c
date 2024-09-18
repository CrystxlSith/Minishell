/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:21:12 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/09/18 11:22:57 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_nb_fd(int fd, int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	len = print_str_fd(fd, str);
	free(str);
	return (len);
}
