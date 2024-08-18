/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:43:18 by seojkim           #+#    #+#             */
/*   Updated: 2023/11/12 17:06:56 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	int					i;

	i = 0;
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (dst >= src && src + n >= dst)
		return (dst);
	else if (src >= dst && dst + n > src)
		return (dst);
	while (n > 0)
	{
		*(dest + i) = *(source + i);
		i++;
		n--;
	}
	return (dst);
}
