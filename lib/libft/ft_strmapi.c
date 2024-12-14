/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:51:52 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:51:53 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buf;
	size_t	i;

	buf = ft_strdup(s);
	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i])
	{
		buf[i] = f(i, buf[i]);
		i++;
	}
	return (buf);
}
