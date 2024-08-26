/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:31:53 by ptheo             #+#    #+#             */
/*   Updated: 2024/08/26 16:38:09 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>

# define HERE_DOC "here_doc"

typedef struct s_data
{
	int		fd1;
	int		fd2;
	int		len;
	char	**cmd;
	char	**envp;
	int		end[2];
	int		fd[2];
}				t_data;

/* PIPEX */
int		pipex(t_data *data, int start);
int		execute_cmd(t_data *data, int i);
char	*ft_strfind(char **str, char *to_find);
char	**ft_split_add(char const *s, char c);
int		cmd_side(t_data *data, int i);
int		cmdlast_side(t_data *data, int i);
int		cmdlen(char **cmd);

/* HERE_DOC */
int		check_heredoc(char	*str, char *str2, int n);
int		pipex_heredoc(t_data *data);

#endif