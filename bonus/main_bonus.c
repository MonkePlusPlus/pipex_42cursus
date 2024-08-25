/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:41:10 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/25 03:01:54 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac >= 5)
	{
		data.fd1 = open(av[1], O_RDONLY);
		data.fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		data.cmd = av;
		data.envp = envp;
		if (data.fd1 < 0 || data.fd2 < 0)
			return (perror("Error opening fds"), 1);
		pipex(&data);
		close(data.fd1);
		close(data.fd2);
	}
	else
		return (perror("Error number argument"), 1);
	return (0);
}
