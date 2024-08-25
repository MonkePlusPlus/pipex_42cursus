/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/25 17:36:58 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmdlen(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	cmd_side(t_data *data, int i)
{
	pid_t	p;

	printf("fd : %d\n", data->fd);
	pipe(data->end);
	p = fork();
	if (p < 0)
		return (perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(data->fd, STDIN_FILENO);
		dup2(data->end[1], STDOUT_FILENO);
		if (execute_cmd(data, i) == -1)
			return (-1);
	}
	else
	{
		dup2(STDIN_FILENO, data->fd);
		dup2(STDOUT_FILENO, data->end[1]);
		data->fd = data->end[0];
	}
	return (0);
}

int	cmdlast_side(t_data *data, int i)
{
	pid_t	p;

	printf("fd : %d\n", data->fd);
	p = fork();
	if (p < 0)
		return (perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(data->end[0], STDIN_FILENO);
		dup2(data->fd2, STDOUT_FILENO);
		if (execute_cmd(data, i) == -1)
			return (-1);
	}
	return (0);
}
