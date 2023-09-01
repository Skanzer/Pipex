/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:39:41 by szerzeri          #+#    #+#             */
/*   Updated: 2023/07/23 19:08:24 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

int		open_file(char *file_name, int w_r);
char	*get_env(char **env);
char	*get_path(char **env, char *cmd);
void	free_tab(char **tab);
void	exec(char **env, char **cmd);
void	run_child(int *p_fd, char **argv, char **env);
void	run_parent(int *p_fd, char **argv, char **env);

#endif
