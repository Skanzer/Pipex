/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:39:24 by szerzeri          #+#    #+#             */
/*   Updated: 2023/07/24 00:10:10 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char **env, char **cmd)
{
	char	*path;

	path = get_path(env, cmd[0]);
	if (execve(path, cmd, env) == -1)
	{
		perror(cmd[0]);
		free_tab(cmd);
		exit(EXIT_FAILURE);
	}
}

void	run_child(int *p_fd, char **argv, char **env)
{
	char	**cmd;
	int		fd;

	cmd = ft_split(argv[2], ' ');
	fd = open_file(argv[1], 0);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	exec(env, cmd);
}

void	run_parent(int *p_fd, char **argv, char **env)
{
	char	**cmd;
	int		fd;

	cmd = ft_split(argv[3], ' ');
	fd = open_file(argv[4], 1);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[1]);
	exec(env, cmd);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (argc != 5)
		exit(EXIT_SUCCESS);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		run_child(p_fd, argv, env);
	run_parent(p_fd, argv, env);
	return (0);
}
