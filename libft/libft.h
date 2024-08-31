/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:36:35 by wbelyne           #+#    #+#             */
/*   Updated: 2024/07/22 08:02:07 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}	t_list;
char	*ft_uitoa(unsigned long int n);
char	*ft_strcat(char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		ft_print_ptr(unsigned long int i);
int		print_nb(int nb);
int		ft_print_hex(unsigned int i, char c);
int		print_char(int c);
int		print_unsigned(unsigned int nb);
int		print_str(char *str);
int		print_nb(int nb);
int		print_char(int c);
int		ft_printf(const char *s, ...);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalpha(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isascii(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_lstsize(t_list *lst);
int		gnl_strchr_i(const char *s, int c);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
char	*ft_strdup(const char *s);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *dest, const char *src);
void	ft_strclr(char *s);
void	ft_putnbr(int n);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_gnl(char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*gnl_shrink_buffer(char *buf, char *line);
char	*gnl_expand_buffer(char *buf, int fd);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_newread(int fd);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	gnl_strlen(const char *s);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
size_t	gnl_strlcat(char *dst, const char *src, size_t size);
#endif
