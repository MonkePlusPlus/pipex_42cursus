/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:31:53 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/25 17:37:08 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct  s_data
{
    int     fd1;
    int     fd2;
	int		fd;
    char    **cmd;
    char    **envp;
    int   	end[2];
}               t_data;


int		pipex(t_data *data);
int		execute_cmd(t_data *data, int i);
char	*ft_strfind(char **str, char *to_find);
char	**ft_split_add(char const *s, char c);
int		cmd_side(t_data *data, int i);
int		cmdlast_side(t_data *data, int i);
int 	cmdlen(char **cmd);

#endif