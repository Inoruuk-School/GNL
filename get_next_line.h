/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:39:11 by asiaux       #+#   ##    ##    #+#       */
<<<<<<< HEAD
/*   Updated: 2017/12/26 20:01:39 by asiaux      ###    #+. /#+    ###.fr     */
=======
/*   Updated: 2017/12/26 19:27:47 by asiaux      ###    #+. /#+    ###.fr     */
>>>>>>> 43f396e5471e526a1b827dec7301f6aa7492f766
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10
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
<<<<<<< HEAD
t_list					*ft_seek_n_fill(t_list &*lst, char *buff, const int ret);
=======
t_list					*ft_seek_n_fill(t_list *lst, char *buff, const int ret);
>>>>>>> 43f396e5471e526a1b827dec7301f6aa7492f766

#endif
