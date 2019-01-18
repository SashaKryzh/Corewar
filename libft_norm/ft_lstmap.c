/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 09:13:38 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/25 09:13:38 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;
	t_list	*cur;

	if (!lst || !f)
		return (NULL);
	res = (*f)(lst);
	cur = res;
	lst = lst->next;
	while (lst)
	{
		tmp = (*f)(lst);
		cur->next = tmp;
		cur = cur->next;
		lst = lst->next;
	}
	return (res);
}
