/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:41:53 by ebouvier          #+#    #+#             */
/*   Updated: 2023/06/04 20:22:34 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "pipex_struct.h"
# define HERE_DOC_PATH "/tmp/here_doc.tmp"
int		check_here_doc(char *av);
void	check_args_bonus(int ac, char **av);
void	handle_here_doc(t_pipe *p);
#endif