/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/26 01:40:04 by ptheo            ###   ########.fr       */
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

	printf("%d -> fd[0] : %d fd[1] : %d\n", i, data->fd[0], data->fd[1]);
	pipe(data->end);
	p = fork();
	if (p < 0)
		return (perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->end[1], STDOUT_FILENO);
		if (execute_cmd(data, i) == -1)
			return (-1);
	}
	else
	{
		dup2(STDIN_FILENO, data->fd[0]);
		dup2(STDOUT_FILENO, data->end[1]);
		close(data->fd[0]);
		if (i != 2)
			close(data->fd[1]);
		data->fd[0] = data->end[0];
		data->fd[1] = data->end[1];
	}
	printf("end process\n");
	return (0);
}

int	cmdlast_side(t_data *data, int i)
{
	pid_t	p;

	printf("%d -> fd[0] : %d fd[1] : %d\n", i, data->fd[0], data->fd[1]);
	p = fork();
	if (p < 0)
		return (perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->fd2, STDOUT_FILENO);
		if (execute_cmd(data, i) == -1)
			return (-1);
	}
	else
	{
		close(data->fd[0]);
		close(data->fd[1]);
	}
	printf("end process\n");
	return (0);
}
