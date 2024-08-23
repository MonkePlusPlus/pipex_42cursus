/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:41:10 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/23 16:06:57 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;
	
	if (ac == 5)
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd1 < 0 || fd2 < 0)
			return (perror("Error opening fds"), 1);
		pipex(fd1, fd2, av, envp);
	}
	else
		return (perror("Error number argument"), 1);
	return (0);
}

/*

avoir child cmd et parent cmd
dup2 fd1 to stdin et dup2 end[1] to stdout -> execve prend stdin comme input et stdout comme output
read end[1] en mettant dans end[0]
dup2 end[0] stdin et dup2 fd2 stdout
execve cmd2

*/