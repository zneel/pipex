/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:38:32 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/03 17:42:44 by ebouvier         ###   ########.fr       */
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
	int		fdin;
	int		fdout;
	char	*limiter;
	int		ac;
	char	**av;
	char	**env;
	int		in_save;
	int		out_save;
}			t_pipe;

typedef struct s_cmd
{
	char	**cmd;
	char	*raw_cmd;
	int		has_pipe;
}			t_cmd;

void		pipex(t_pipe *p);
void		close_pipe(int *fd);
void		free_split(char **cmd);
char		**get_cmd(char *full_cmd, char **env);
void		exit_error(int fd[2]);
t_cmd		*new_cmd(char *raw_cmd, int has_pipe);
void		print_t_cmd(t_cmd *cmd);
void		cmd_clean(t_cmd *cmd);
void		cmds_clean(t_list *cmds);
void		execute(t_cmd *cmd, char **env);
int			add_cmd(t_list **cmds, t_cmd *cmd);
int			pipe_fork(t_cmd *cmd, pid_t *pid, int fd[2], t_pipe *p);
void		wait_for_cmds(t_list *cmds);

#endif