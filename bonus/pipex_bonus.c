/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:41:56 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/26 16:41:05 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	pipex(t_data *data, int start)
{
	int		i;
	int		len;

	i = start;
	len = data->len;
	while (i < len - 2)
	{
		if (cmd_side(data, i) == -1)
			return (-1);
		i++;
	}
	if (cmdlast_side(data, i) == -1)
		return (-1);
	i = start;
	while (i < len - 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (0);
}

int	execute_cmd(t_data *data, int i)
{
	char	**argcmd;
	char	**allpath;
	char	*path;
	char	*path_cmd;

	path = ft_strfind(data->envp, "PATH=");
	argcmd = ft_split(data->cmd[i], ' ');
	allpath = ft_split_add(path, ':');
	while (*allpath != NULL)
	{
		path_cmd = ft_strjoin(*allpath, argcmd[0]);
		if (path_cmd == NULL)
			return (perror("Error malloc"), -1);
		execve(path_cmd, argcmd, data->envp);
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
