/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:41:10 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 21:17:41 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac >= 5)
	{
		
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd1 < 0 || fd2 < 0)
			return (perror("Error opening fds"), 1);
		pipex(fd1, fd2, av, envp);
		close(fd1);
		close(fd2);
	}
	else
		return (perror("Error number argument"), 1);
	return (0);
}
