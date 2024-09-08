/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 01:51:58 by seojkim           #+#    #+#             */
/*   Updated: 2024/09/07 01:52:07 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*u_s1;
	const unsigned char	*u_s2;
	int					i;

	u_s1 = (const unsigned char *)s1;
	u_s2 = (const unsigned char *)s2;
	i = 0;
	while (u_s1[i] || u_s2[i])
	{
		if (u_s1[i] > u_s2[i])
			return (1);
		else if (u_s1[i] < u_s2[i])
			return (-1);
		i++;
	}
	return (0);
}
