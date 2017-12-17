/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/26 14:08:30 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/06 12:34:53 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *var, size_t size)
{
	void	*tmp;

	if(!(tmp = malloc(size)))
		return (NULL);
	ft_memcpy(tmp, var, size);
	free(var);
	return (tmp);
}
