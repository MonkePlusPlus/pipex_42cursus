/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:41:10 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/13 01:01:00 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_freesplit(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

int	init_data(t_data *data, int ac, char **av, char **envp)
{
	data->len = ac;
	data->heredoc = 1;
	data->cmd = av;
	data->envp = envp;
	data->count = 0;
	data->allpath = NULL;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac >= 5)
	{
		init_data(&data, ac, av, envp);
		if (ac > 5 && check_heredoc(av[1], HERE_DOC, 0))
			pipex_heredoc(&data);
		else
		{
			data.fd1 = open(av[1], O_RDONLY);
			data.fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
			data.fd[0] = data.fd1;
			if (data.fd1 < 0 || data.fd2 < 0)
				return (perror("Error opening fds"), 1);
			data.tabpid = (pid_t *)malloc(sizeof(pid_t) * data.len - 1);
			if (data.tabpid == NULL)
				return (ft_putstr_fd("Error pid tab\n", 2),
					close(data.fd1), close(data.fd2), 1);
			pipex(&data);
		}
		ft_freesplit(data.allpath);
		free(data.tabpid);
		close(data.fd2);
	}
	else
		return (ft_putstr_fd("Error number argument\n", 2), 1);
	return (0);
}
