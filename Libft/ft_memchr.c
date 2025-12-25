/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:29:24 by britela-          #+#    #+#             */
/*   Updated: 2025/04/18 15:12:50 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	cc;

	i = 0;
	str = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == cc)
		{
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	char	*mot;
	char	*res;

	mot = "Bradley";
	res = ft_memchr(mot, 'd', 7); // pour la taille du mot
	
	printf("%s", res);
	return (0);
}*/
