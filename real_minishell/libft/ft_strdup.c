/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:54:15 by seojkim           #+#    #+#             */
/*   Updated: 2024/08/15 13:08:26 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*address;

	address = (char *)malloc(size + 1);
	if (address == NULL)
		return (0);
	ft_strlcpy(address, s1, size + 1);
	return (address);
}

char	*ft_strdup(const char *s1)
{
	char	*address;

	address = (char *)malloc((ft_strlen(s1) + 1));
	if (address == NULL)
		return (0);
	ft_strlcpy(address, s1, ft_strlen(s1) + 1);
	return (address);
}
