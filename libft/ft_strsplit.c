/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 11:38:00 by okryzhan          #+#    #+#             */
/*   Updated: 2018/10/24 11:38:00 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_and_null(char **tab, size_t k)
{
	size_t i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_words(char *s, char c)
{
	size_t	i;
	size_t	count;
	int		isword;

	i = 0;
	count = 0;
	isword = 1;
	while (s[i])
	{
		if (s[i] != c && isword == 1)
		{
			count++;
			isword = 0;
		}
		if (s[i] == c)
			isword = 1;
		i++;
	}
	return (count);
}

static size_t	ft_word(char *s, char c)
{
	size_t len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void		ft_setvalues(size_t *i, size_t *k)
{
	*i = -1;
	*k = 0;
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (ft_words((char *)s, c) + 1))))
		return (NULL);
	ft_setvalues(&i, &k);
	while (s[++i])
	{
		if (s[i] != c)
		{
			j = -1;
			if ((tab[k] = ft_strnew(ft_word((char *)&s[i], c))) == NULL)
				return (ft_free_and_null(tab, k));
			while (s[i] != c && s[i])
				tab[k][++j] = s[i++];
			tab[++k] = 0;
		}
		if (s[i] == '\0')
			break ;
	}
	return (tab);
}
