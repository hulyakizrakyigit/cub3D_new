/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:50:24 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:50:25 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*new;
	void	*tc;

	if (!lst || !f || !del)
		return (NULL);
	root = NULL;
	while (lst)
	{
		tc = f(lst->content);
		if (!tc)
			return (ft_lstclear(&root, del), NULL);
		new = ft_lstnew(tc);
		if (!new)
			return (ft_lstclear(&root, del), del(tc), NULL);
		ft_lstadd_back(&root, new);
		lst = lst->next;
	}
	return (root);
}
