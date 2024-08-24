/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:41:56 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 19:05:27 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(int fd1, int fd2, char **cmd, char **envp)
{
	int		end[2];
	int		status;

	pipe(end);
	if (cmd1_side(fd1, end, cmd, envp) == -1)
		return (close(end[0]), close(end[1]), -1);
	if (cmd2_side(fd2, end, cmd, envp) == -1)
		return (close(end[0]), close(end[1]), -1);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
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
