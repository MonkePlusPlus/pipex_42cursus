/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:00:42 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 21:15:53 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	count_words_add(char const *s, char c)
{
	int	count;
	int	i;
	int	first;

	i = 0;
	first = 1;
	count = 0;
	while (s[i])
	{
		if (first && s[i] != c)
		{
			first = 0;
			count++;
		}
		if (!first && s[i] == c)
			first = 1;
		i++;
	}
	return (count);
}

int	check_ifc_add(char const *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	fullfill_add(char const *s, char *result, int start, int end)
{
	int	i;

	i = 0;
	while (s[start] && start < end)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '/';
	result[i + 1] = '\0';
}

void	*free_error_add(char **p, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

char	**ft_split_add(char const *s, char c)
{
	char	**result;
	int		first;
	int		i;
	int		index;

	i = 0;
	index = 0;
	result = malloc((count_words_add(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			first = i;
			i = check_ifc_add(s, i, c);
			result[index] = malloc(((i - first) + 2) * sizeof(char));
			if (result[index] == NULL)
				return (free_error_add(result, index));
			fullfill_add(s, result[index], first, i--);
			index++;
		}
		i++;
	}
	return (result[index] = 0, result);
}
