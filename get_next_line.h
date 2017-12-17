/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:39:11 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/17 05:19:58 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_gnl
{
	int					fd;
	t_list				*lst;
	struct s_gnl		*nextgnl;
}						t_gnl;

int						get_next_line(const int fd, char **line);

#endif
