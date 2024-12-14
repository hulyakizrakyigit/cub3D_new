/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkizrak- <hkizrak-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:50:42 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:50:43 by hkizrak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;

	if ((!s1 && !s2) || n == 0)
		return (0);
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (--n)
	{
		if (*ps1 != *ps2)
			return ((unsigned char) *ps1 - (unsigned char) *ps2);
		ps1++;
		ps2++;
	}
	return ((unsigned char) *ps1 - (unsigned char) *ps2);
}
