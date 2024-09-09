/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:02:45 by seojkim           #+#    #+#             */
/*   Updated: 2023/11/12 17:09:18 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;
	int					i;

	u_s1 = (const unsigned char *)s1;
	u_s2 = (const unsigned char *)s2;
	i = 0;
	while ((u_s1[i] || u_s2[i]) && n)
	{
		if (u_s1[i] > u_s2[i])
			return (1);
		else if (u_s1[i] < u_s2[i])
			return (-1);
		i++;
		n--;
	}
	return (0);
}
