/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andqueir <andreia@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:19:55 by andqueir          #+#    #+#             */
/*   Updated: 2025/11/21 11:35:00 by andqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

# define MAX_FD 10240

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

//main:
char	*get_next_line(int fd);

//utils:
char		*ft_strdup(char *s);
size_t	ft_strlen(const char *str);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char *s, unsigned int start, size_t len);

#endif