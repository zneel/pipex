/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:38:32 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/01 18:57:49 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "lists.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int		fd1;
	int		fd2;
	char	*limiter;
	int		ac;
	char	**av;
	char	**env;
}			t_pipe;

void		pipe_commands(t_pipe *p);
void		close_pipe(int *fd);
void		free_split(char **cmd);
char		**get_cmd(char *full_cmd, char **env);
void		exit_error(int fd[2]);

#endif