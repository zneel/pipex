/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:32:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/24 13:48:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_here_doc(char *av)
{
	if (ft_strncmp(av, "here_doc", 9) == 0)
		return (1);
	return (0);
}

int	check_good_tmp(void)
{
	int	i;
	int	fd;

	i = 10000;
	if (access(HERE_DOC_PATH, F_OK) == 0)
		unlink(HERE_DOC_PATH);
	while (access(HERE_DOC_PATH, F_OK) != 0 && i)
	{
		fd = open(HERE_DOC_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd > 0)
			return (fd);
		i--;
	}
	return (-1);
}

int	here_doc_prompt(int fd, t_pipe *p)
{
	char	*line;

	ft_putstr_fd("pipe heredoc> ", 1);
	line = get_next_line(0);
	while (1)
	{
		if (!line)
		{
			get_next_line(-1);
			return (-1);
		}
		if (ft_strncmp(line, p->limiter, ft_strlen(p->limiter)) == 0)
		{
			get_next_line(-1);
			free(line);
			break ;
		}
		ft_putstr_fd("pipe heredoc> ", 1);
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	return (0);
}

void	handle_here_doc(t_pipe *p)
{
	int	fd;
	int	ret;

	fd = check_good_tmp();
	if (fd < 0)
		exit(errno);
	p->limiter = ft_strdup(p->av[2]);
	if (!p->limiter)
		exit(1);
	ret = here_doc_prompt(fd, p);
	free(p->limiter);
	close(fd);
	if (ret == -1)
		exit(1);
	fd = open(HERE_DOC_PATH, O_RDONLY);
	p->fd_in = fd;
}
