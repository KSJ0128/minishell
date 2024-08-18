/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojkim <seojkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:04:03 by seojkim           #+#    #+#             */
/*   Updated: 2023/11/15 08:53:04 by seojkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (0);
	new_lst = NULL;
	while (lst != NULL)
	{
		tmp = f(lst->content);
		new_node = ft_lstnew(tmp);
		if (new_node == NULL)
		{
			del(tmp);
			ft_lstclear(&new_lst, del);
			free(new_lst);
			return (0);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
