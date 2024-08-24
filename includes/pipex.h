/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:31:53 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/24 18:37:57 by ptheo            ###   ########.fr       */
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

int		pipex(int fd1, int fd2, char **cmd, char **envp);
int		execute_cmd(char *cmd, char **envp);
char	*ft_strfind(char **str, char *to_find);
char	**ft_split_add(char const *s, char c);
int		cmd1_side(int fd2, int end[2], char **cmd, char **envp);
int		cmd2_side(int fd1, int end[2], char **cmd, char **envp);

#endif