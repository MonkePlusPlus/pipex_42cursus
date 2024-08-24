/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:41:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 19:04:24 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cmd1_side(int fd1, int end[2], char **cmd, char **envp)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		return (close(end[0]), close(end[1]), perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(end[1], STDOUT_FILENO);
		if (execute_cmd(cmd[2], envp) == -1)
			return (-1);
	}
	else
	{
		dup2(STDOUT_FILENO, end[1]);
		dup2(STDIN_FILENO, fd1);
	}
	return (0);
}

int	cmd2_side(int fd2, int end[2], char **cmd, char **envp)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		return (close(end[0]), close(end[1]), perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(end[0], STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		if (execute_cmd(cmd[3], envp) == -1)
			return (-1);
	}
	return (0);
}	
