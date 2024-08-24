/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:41:56 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 21:25:45 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	pipex(int fd1, int fd2, char **cmd, char **envp)
{
	int		end[2];
	int		status;
	int		i;
	int		fd;

	pipe(end);
	i = 2;
	fd = fd1;
	while (i < cmdlen(cmd) - 2)
	{
		if (cmd_side(fd, end, cmd[i], envp) == -1)
			return (close(end[0]), close(end[1]), -1);
		i++;
		fd = end[0];
	}
	if (cmdlast_side(fd2, end, cmd[i], envp) == -1)
		return (close(end[0]), close(end[1]), -1);
	i = 2;
	while (i < cmdlen(cmd) - 1)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	close(end[0]);
	close(end[1]);
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
		execve(path_cmd, argcmd, envp);
		free(path_cmd);
		allpath++;
	}
	perror("Error command");
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
