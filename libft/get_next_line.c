/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:25:59 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/07/23 07:37:17 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_start(char	*str)
{
	int		i;
	int		j;
	char	*adv_str;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	adv_str = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!adv_str)
		return (NULL);
	i += 1;
	while (str[i])
	{
		adv_str[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (adv_str);
}

char	*return_line(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	newstr = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		newstr[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		newstr[i++] = '\n';
	return (newstr);
}

char	*next_line(char *str, int fd)
{
	char	*buf;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	bytes_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			bytes_read = 0;
			return (NULL);
		}
		buf[bytes_read] = 0;
		str = ft_strjoin_gnl(str, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (str[fd])
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = next_line(str[fd], fd);
	if (!str[fd])
		return (NULL);
	line = return_line(str[fd]);
	str[fd] = new_start(str[fd]);
	return (line);
}

// int main(void) {
//     int fd1, fd2, fd3;
//     char *line;
//     fd1 = open("text.txt", O_RDONLY);
//     if (fd1 < 0) {
//         perror("Error opening test.txt");
//         return 1;
//     }
//     fd2 = open("test2.txt", O_RDONLY);
//     if (fd2 < 0) {
//         perror("Error opening test2.txt");
//         return 1;
//     }
//     fd3 = open("test3.txt", O_RDONLY);
//     if (fd3 < 0) {
//         perror("Error opening test3.txt");
//         return 1;
//     }
//     line = get_next_line(fd1);
//     if (line) {
//         printf("Test1: %s\n", line);
//         free(line);
//     }
//     line = get_next_line(fd2);
//     if (line) {
//         printf("Test2: %s\n", line);
//         free(line);
//     }
//     line = get_next_line(fd3);
//     if (line) {
//         printf("Test3: %s\n", line);
//         free(line);
//     }
//     line = get_next_line(fd1);
//     if (line) {
//         printf("Test1: %s\n", line);
//         free(line);
//     }
//     line = get_next_line(fd2);
//     if (line) {
//         printf("Test2: %s\n", line);
//         free(line);
//     }
//     line = get_next_line(fd3);
//     if (line) {
//         printf("Test3: %s\n", line);
//         free(line);
//     }
//     close(fd1);
//     close(fd2);
//     close(fd3);
//     return 0;
// }
