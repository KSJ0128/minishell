/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:25:19 by seojkim           #+#    #+#             */
/*   Updated: 2023/11/12 17:01:15 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*trim;
	unsigned int	f;
	unsigned int	b;

	if (s1[0] == '\0' || set[0] == '\0')
		return (ft_strdup(s1));
	f = 0;
	b = ft_strlen(s1);
	while (ft_strchr(set, s1[f]) != 0 && s1[f] != '\0')
		f++;
	while (ft_strchr(set, s1[b - 1]) != 0 && b > f)
		b--;
	trim = (char *)malloc(b - f + 1);
	if (trim == NULL)
		return (0);
	ft_strlcpy(trim, s1 + f, b - f + 1);
	return (trim);
}
