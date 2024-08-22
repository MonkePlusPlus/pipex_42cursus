/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:41:56 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/22 18:23:16 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int fd1, int fd2, char **cmd, char **envp)
{
	pid_t	p;
	int		status;
	int		end[2];

	pipe(end);
	p = fork();
	if (p < 0)
		return (close(end[0]), close(end[1]), perror("Error fork"), -1);
	if (p == 0)
	{
		dup2(fd1, STDIN_FILENO);
		dup2(end[1], STDOUT_FILENO);
		execute_cmd(cmd[2], envp);
	}
	else
	{
		waitpid(0, &status, 0);
		dup2(end[0], STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		execute_cmd(cmd[3], envp);
	}
	return (0);
}

void	print_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	execute_cmd(char *cmd, char **envp)
{
	char	**argcmd;
	char	**allpath;
	char	*path;
	char	*path_cmd;

	path = ft_strfind(envp, "PATH=");
	argcmd = ft_split(cmd, ' ');
	allpath = ft_split_add(path, ':');
	while (*allpath != NULL)
	{
		path_cmd = ft_strjoin(*allpath, argcmd[0]);
		execve(path_cmd, argcmd + 1, envp);
		free(path_cmd);
		allpath++;
	}
	perror("Error cmd");
	return (-1);
}

char	*ft_strfind(char **str, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] == to_find[j])
			j++;
		if (to_find[j] == 0)
			return (&str[i][j]);
		i++;
	}
	return (NULL);
}
