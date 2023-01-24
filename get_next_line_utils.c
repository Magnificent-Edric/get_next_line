/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:12:53 by medric            #+#    #+#             */
/*   Updated: 2021/11/13 17:12:53 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->lenght = 0;
	new->next = NULL;
	return (new);
}

int	check(t_buffer *buff, t_list *list, t_result *res)
{
	int	flg;

	flg = 0;
	while (buff->read_chr > 0 && buff->buffer[buff->next_chr] != '\n')
	{
		list->buffer[list->lenght++] = buff->buffer[buff->next_chr++];
		buff->read_chr--;
		res->size_buff++;
	}
	if (buff->read_chr > 0 && buff->buffer[buff->next_chr] == '\n')
	{
		list->buffer[list->lenght++] = buff->buffer[buff->next_chr++];
		res->size_buff++;
		buff->read_chr--;
		flg = 1;
	}
	if (buff->read_chr == 0)
		buff->next_chr = 0;
	return (flg);
}

t_list	*line_list(t_buffer *buff, t_list *list, t_result *res, int fd)
{
	t_buffer	*tmp;

	if (check(buff, list, res))
		return (list);
	tmp = buff;
	tmp->read_chr = read(fd, tmp->buffer, BUFFER_SIZE);
	while (tmp->read_chr > 0)
	{
		list->next = ft_lstnew();
		if (!list->next)
			return (NULL);
		list = list->next;
		if (!tmp)
			return (NULL);
		if (check(buff, list, res) == 1)
			return (list);
		tmp->read_chr = read(fd, tmp->buffer, BUFFER_SIZE);
	}
	if (buff->read_chr == -1)
	{
		buff->read_chr = 0;
		return (NULL);
	}
	return (list);
}

char	*creat_str(t_list *list, t_result *res)
{
	size_t	len_str;
	size_t	list_len;
	t_list	*lst;

	lst = list;
	len_str = 0;
	if (res->size_buff == 0)
		return (NULL);
	res->r = (char *)malloc(sizeof(char) * (++res->size_buff));
	if (!res->r)
		return (NULL);
	while (lst != NULL)
	{
		list_len = 0;
		while (list_len < lst->lenght)
		{
			res->r[len_str] = lst->buffer[list_len];
			list_len++;
			len_str++;
		}
		lst = lst->next;
	}
	res->r[res->size_buff - 1] = '\0';
	return (res->r);
}
