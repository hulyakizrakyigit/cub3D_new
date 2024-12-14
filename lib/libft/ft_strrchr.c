/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:52:04 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:52:05 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	size_t	len;

	len = ft_strlen(s);
	if ((char) c == '\0')
		if (s[len] == '\0')
			return ((char *) &s[len]);
	i = len - 1;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}
