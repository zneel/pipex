/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:57:24 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 16:34:36 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int fd[2])
{
	if (fd[READ] > 0)
		close(fd[READ]);
	if (fd[WRITE] > 0)
		close(fd[WRITE]);
}

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	exit_error(int fd[2])
{
	close_pipe(fd);
	exit(errno);
}
