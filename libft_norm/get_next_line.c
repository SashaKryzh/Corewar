/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzakala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:19:34 by pzakala           #+#    #+#             */
/*   Updated: 2018/11/07 11:50:16 by pzakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_lst(t_list **head, size_t fd)
{
	t_list *save;

	if (!(*head))
	{
		if (!(*head = ft_lstnew("\0", fd)))
			return (NULL);
		return (*head);
	}
	save = *head;
	if (save->content_size == fd)
		return (save);
	while (save->next)
	{
		if (save->content_size == fd)
			return (save);
		save = save->next;
	}
	if (save->content_size == fd)
		return (save);
	if (!(save->next = ft_lstnew("", fd)))
		return (NULL);
	return (save->next);
}

void	ft_leaks_del(t_list **head, size_t fd)
{
	t_list *save;
	t_list *del;

	save = *head;
	if (save->content_size == fd)
	{
		(*head) = (*head)->next;
		free(save->content);
		free(save);
		return ;
	}
	while (save->next && save->next->content_size != fd)
		save = save->next;
	del = save->next;
	save->next = save->next->next;
	free(del->content);
	free(del);
}

int		ft_cut_join(char **res, char **l, t_list **head, size_t fd)
{
	char	**arr;

	if (ft_strequ(*res, ""))
	{
		ft_leaks_del(head, fd);
		return (0);
	}
	arr = ft_strcut(*res, '\n', ft_strlen(*res));
	if (*res != NULL)
		free(*res);
	*l = ft_strdup(arr[0]);
	*res = ft_strdup(arr[1]);
	ft_listdel(arr);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*lst;
	char			*buff;
	char			*save;
	int				r;

	buff = NULL;
	if (!line || fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	MCHECK(lst = get_lst(&head, fd + 1));
	MCHECK(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1)));
	while ((r = read(fd, buff, BUFF_SIZE)))
	{
		if (r < 0)
			return (-1);
		buff[r] = '\0';
		MCHECK(save = ft_strjoin(lst->content, buff));
		free(lst->content);
		lst->content = save;
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buff);
	return (ft_cut_join((char **)(&(lst->content)), line, &head, fd + 1));
}
