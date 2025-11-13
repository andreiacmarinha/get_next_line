/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andqueir <andreia@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:35:59 by andqueir          #+#    #+#             */
/*   Updated: 2025/11/13 18:01:50 by andqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

//utils:
void		ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);

//mains:
char		*ft_next(char *buffer);
char		*ft_line(char *buffer);
char		*get_next_line(int fd);
char		*read_file(int fd, char *res);
char		*ft_free(char *buffer, char *buf);

#endif