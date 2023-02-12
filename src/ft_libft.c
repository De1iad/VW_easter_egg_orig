/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:51:41 by obibby            #+#    #+#             */
/*   Updated: 2023/02/12 20:10:39 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../car.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		destlen;
	int		srclen;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	while (dest[i] != '\0')
	{
		if (i == size)
			return (size + srclen);
		i++;
	}
	while (src[i - destlen] != '\0' && i < size - 1 && size > 0)
	{
		dest[i] = src[i - destlen];
		i++;
	}
	dest[i] = '\0';
	return (destlen + srclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ptr = malloc(sizeof(char) * len);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, (ft_strlen(s1) + 1));
	ft_strlcat(ptr, s2, len);
	return (ptr);
}
