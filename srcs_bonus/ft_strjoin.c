/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:53:13 by npirard           #+#    #+#             */
/*   Updated: 2024/01/25 18:46:19 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/// @brief Return the number of non empty bytes in a string
/// @param s Null terminated string
/// @return Size if the given string, excluding the null terminating byte
static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/// @brief Try to copy the full length of src after dst,
/// adding a null byte at the end.
/// If the resulting string doesn't fit into dst, size - 1 byte will be copied,
/// assuring the null byte at the end of dst.
/// @param dst The string receiving the concatenation.
/// @param src String to concatenate with dst
/// @param size Full size of the buffer dst.
/// @return The length of the intended resulting string,
/// meaning len(dst) len(src).
/// If dst is not null terminated, return size + len(src)
/// and dst will not be null terminated.
static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l_src;
	size_t	l_dst;

	l_src = ft_strlen(src);
	if (!size)
		return (size + l_src);
	l_dst = ft_strlen(dst);
	if (l_dst >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - l_dst - 1))
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}

/// @brief Try to copy the full length of src into dst,
/// adding a null byte at the end.
/// If src doesn't fit into dst, size - 1 byte wille be copied,
/// assuring the null byte at the end of dst.
/// @param dst Buffer into which src is copied.
/// @param src String to copy into dst
/// @param size Full size of the buffer dst
/// @return The length of the intended dst string, meaning the length of src.
static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && size && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

/// @brief Allocate and return the concatenation of s1 and s2
/// @param s1 Null terminated string
/// @param s2 Null terminated string
/// @return Address of allocated string
/// NULL if allocation fails.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1, size);
	ft_strlcat(buffer, s2, size);
	return (buffer);
}
