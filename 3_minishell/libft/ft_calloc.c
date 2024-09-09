/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:44:13 by seojkim           #+#    #+#             */
/*   Updated: 2023/11/12 17:06:22 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int count, size_t size)
{
	void	*address;

	address = malloc(size * count);
	if (address == NULL)
		return (0);
	ft_memset(address, 0, size * count);
	return (address);
}
