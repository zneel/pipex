/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:43 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 23:04:11 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_if_open(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	pipe_for_first(int pipe_fd[2], int fd_in)
{
	dup2(fd_in, STDIN_FILENO);
	close_if_open(fd_in);
	close_if_open(pipe_fd[READ]);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_if_open(pipe_fd[WRITE]);
}

void	pipe_for_child(int new_pipe[2], int old_pipe[2])
{
	close_if_open(old_pipe[WRITE]);
	dup2(old_pipe[READ], STDIN_FILENO);
	close_if_open(old_pipe[READ]);
	close_if_open(new_pipe[READ]);
	dup2(new_pipe[WRITE], STDOUT_FILENO);
	close_if_open(new_pipe[WRITE]);
}

void	pipe_for_last(int old_pipe[2], int fd_out)
{
	close_if_open(old_pipe[WRITE]);
	dup2(old_pipe[READ], STDIN_FILENO);
	close_if_open(old_pipe[READ]);
	dup2(fd_out, STDOUT_FILENO);
	close_if_open(fd_out);
}
