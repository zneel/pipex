/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:43 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 16:36:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prepare_fd(t_pipe *p)
{
	dup2(p->fd_in, 0);
	close(p->fd_in);
}

void	pipe_for_first(int pipe_fd[2], t_pipe *p)
{
	close(p->fd_out);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_pipe(pipe_fd);
}

void	pipe_for_child(int old_read_pipe, int pipe_fd[2], t_pipe *p)
{
	close(p->fd_out);
	dup2(old_read_pipe, STDIN_FILENO);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_pipe(pipe_fd);
	close(old_read_pipe);
}

void	pipe_for_last(int pipe_fd[2], t_pipe *p)
{
	dup2(p->fd_out, STDOUT_FILENO);
	dup2(pipe_fd[READ], STDIN_FILENO);
	close(p->fd_out);
	close_pipe(pipe_fd);
}
