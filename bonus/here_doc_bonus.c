/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:00:15 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/26 01:40:05 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	check_heredoc(char *str, char *str2, int n)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == str2[i])
		i++;
	if (str2[i] == 0 && str[i] == 0)
		return (1);
	if (n && str2[i] == 0 && str[i] == '\n')
		return (1);
	return (0);
}

int	pipex_heredoc(t_data *data)
{
	char	*line;

	data->fd2 = open(data->cmd[data->len - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd2 < 0)
		return (perror("Error opening fds"), 1);
	pipe(data->fd);
	ft_printf("pipe heredoc>");
	line = get_next_line(0);
	while (line)
	{
		if (check_heredoc(line, data->cmd[2], 1))
		{
			free(line);
			return (0);
		}
		write(data->fd[1], line, ft_strlen(line));
		free(line);
		ft_printf("pipe heredoc>");
		line = get_next_line(0);
	}
	return (-1);
}


