/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:38:32 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 16:32:33 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "lists.h"
# include "pipex_bonus.h"
# include "pipex_struct.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

void	pipex(t_pipe *p);
void	close_pipe(int fd[2]);
void	free_split(char **cmd);
char	**get_cmd(char *full_cmd, char **env);
void	exit_error(int fd[2]);
t_cmd	*new_cmd(char *raw_cmd, int has_pipe, int i);
void	cmd_clean(t_cmd *cmd);
void	cmds_clean(t_list *cmds);
void	execute(t_cmd *cmd, char **env);
int		add_cmd(t_list **cmds, t_cmd *cmd);
void	wait_for_cmds(t_list *cmds);
void	pipe_for_first(int pipe_fd[2], t_pipe *p);
void	pipe_for_child(int old_read_pipe, int pipe_fd[2], t_pipe *p);
void	pipe_for_last(int pipe_fd[2], t_pipe *p);
void	pipe_exec(t_cmd *cmd, int pipe_fd[2], t_pipe *p);

void	print_usage(void);
void	print_here_doc(void);

#endif