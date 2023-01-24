/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:23:31 by medric            #+#    #+#             */
/*   Updated: 2021/11/13 17:23:31 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			buffer[BUFFER_SIZE];
	size_t			lenght;
	struct s_list	*next;
}					t_list;

typedef struct s_result
{
	char	*r;
	size_t	size_buff;
}			t_result;

typedef struct s_buffer
{
	char				buffer[BUFFER_SIZE];
	size_t				next_chr;
	ssize_t				read_chr;
	struct s_buffer		*next;
}						t_buffer;

t_list	*ft_lstnew(void);
void	ft_lstdelone(t_list *list_el);
t_list	*ft_lstadd_back(t_list *new);
void	ft_lstclear(t_list **lst);
char	*get_next_line(int fd);
t_list	*line_list(t_buffer *buff, t_list *list, t_result *res, int fd);
char	*creat_str(t_list *list, t_result *res);
int		check(t_buffer *buff, t_list *list, t_result *res);

#endif
