/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/13 03:13:09 by ptheo            ###   ########.fr       */
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

void	close_fds(t_data *data)
{
	if (data->heredoc != 2)
		close(data->fd1);
	close(data->fd2);
	close(data->end[0]);
	close(data->end[1]);
	close(data->fd[0]);
	if (data->count != 0 || data->heredoc == 2)
		close(data->fd[1]);
}

int	cmd_side(t_data *data, int i)
{
	pipe(data->end);
	data->tabpid[data->count] = fork();
	if (data->tabpid[data->count] < 0)
		return (perror("Error fork"), close_fds(data), -1);
	if (data->tabpid[data->count] == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->end[1], STDOUT_FILENO);
		close_fds(data);
		if (execute_cmd(data, i) == -1)
			return (close_fds(data), -1);
	}
	else
	{
		dup2(STDIN_FILENO, data->fd[0]);
		dup2(STDOUT_FILENO, data->end[1]);
		close(data->fd[0]);
		if (i > 3)
			close(data->fd[1]);
		data->fd[0] = data->end[0];
		data->fd[1] = data->end[1];
	}
	data->count++;
	return (0);
}

int	cmdlast_side(t_data *data, int i)
{
	data->tabpid[data->count] = fork();
	if (data->tabpid[data->count] < 0)
		return (perror("Error fork"), -1);
	if (data->tabpid[data->count] == 0)
	{
		dup2(data->fd[0], STDIN_FILENO);
		dup2(data->fd2, STDOUT_FILENO);
		close_fds(data);
		if (execute_cmd(data, i) == -1)
			return (close_fds(data), -1);
	}
	else
	{
		if (data->argcmd != NULL)
			ft_freesplit(data->argcmd);
		if (data->path_cmd != NULL)
			free(data->path_cmd);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	return (0);
}
