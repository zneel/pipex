/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:24:39 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/05 22:06:29 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCT_H
# define PIPEX_STRUCT_H

typedef struct s_pipe
{
	int		fd_in;
	int		fd_out;
	char	*limiter;
	int		here_doc;
	int		ac;
	char	**av;
	char	**env;
	int		last_status;
}			t_pipe;

typedef struct s_cmd
{
	char	**cmd;
	char	*raw_cmd;
	int		has_pipe;
	int		index;
}			t_cmd;

#endif