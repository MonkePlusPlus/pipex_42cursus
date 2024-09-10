/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:41:56 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/09 19:50:18 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	pipex(t_data *data, int start)
{
	int		i;
	int		len;

	if (create_path(data) == -1)
		return (-1);
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

int	execute_cmd(t_data *data, int index)
{
	int		i;

	i = -1;
	if (data->argcmd != NULL)
		ft_freesplit(data->argcmd);
	if (data->path_cmd != NULL)
		free(data->path_cmd);
	data->argcmd = ft_split(data->cmd[index], ' ');
	if (data->argcmd == NULL)
		return (-1);
	while (data->allpath[++i] != NULL)
	{
		if (access(data->cmd[index], X_OK) == 0)
			data->path_cmd = data->cmd[index];
		else
			data->path_cmd = ft_strjoin(data->allpath[i], data->argcmd[0]);
		if (data->path_cmd == NULL)
			return (perror("Error malloc"), ft_freesplit(data->argcmd), -1);
		execve(data->path_cmd, data->argcmd, data->envp);
		free(data->path_cmd);
	}
	ft_putstr_fd("Error: command not found: ", 2);
	ft_putstr_fd(data->argcmd[0], 2);
	ft_putstr_fd("\n", 2);
	return (ft_freesplit(data->argcmd), data->argcmd = NULL, -1);
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

int	create_path(t_data *data)
{
	char	*path;

	path = ft_strfind(data->envp, "PATH=");
	data->allpath = ft_split_add(path, ':');
	if (data->allpath == NULL)
		return (perror("Error malloc"), -1);
	data->path_cmd = NULL;
	data->argcmd = NULL;
	return (0);
}
