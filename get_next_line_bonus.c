/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:19:24 by medric            #+#    #+#             */
/*   Updated: 2021/11/13 17:19:24 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_res(t_result *res)
{
	res->r = NULL;
	res->size_buff = 0;
}

void	ft_lstdelone(t_list *list_el)
{
	if (!list_el)
		return ;
	free(list_el);
}

t_list	*ft_lstadd_back(t_list *new)
{
	if (!new)
		return (NULL);
	new->next = ft_lstnew();
	return (new->next);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

char	*get_next_line(int fd)
{
	static t_buffer		buffer[OPEN_MAX];
	t_list				*list;
	t_result			res;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ft_res(&res);
	list = ft_lstnew();
	if (!list)
		return (NULL);
	if (!(line_list(&buffer[fd], list, &res, fd)))
	{
		ft_lstclear(&list);
		return (NULL);
	}
	creat_str(list, &res);
	ft_lstclear(&list);
	return (res.r);
}
