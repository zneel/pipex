/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:43 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/04 16:20:38 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_for_first(int pipe_fd[2])
{
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_pipe(pipe_fd);
}

void	pipe_for_child(int old_read_pipe, int pipe_fd[2])
{
	dup2(old_read_pipe, STDIN_FILENO);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_pipe(pipe_fd);
	close(old_read_pipe);
}

void	pipe_for_last(int pipe_fd[2], t_pipe *p)
{
	dup2(p->fd_out, 1);
	close(p->fd_out);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close_pipe(pipe_fd);
}
