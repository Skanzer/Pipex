/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szerzeri <szerzeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:10:04 by szerzeri          #+#    #+#             */
/*   Updated: 2023/07/23 21:57:37 by szerzeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, int w_r)
{
	int	ret;

	if (w_r == 0)
		ret = open(file_name, O_RDONLY, 0777);
	else
		ret = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
	{
		perror(file_name);
		exit (EXIT_FAILURE);
	}
	return (ret);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
}

char	*get_env(char **env)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		path = ft_substr(env[i], 0, j);
		if (ft_strncmp(path, "PATH", 4) == 0)
		{
			free(path);
			return (env[i] + j);
		}
		else
		{
			free(path);
			i++;
		}
	}
	return (NULL);
}

char	*get_path(char **env, char *cmd)
{
	char	*path;
	char	*tmp;
	char	*env_path;
	char	**cmd_path;
	int		i;

	i = 0;
	env_path = get_env(env);
	cmd_path = ft_split(env_path, ':');
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i++], "/");
		path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(path, F_OK | R_OK) == 0)
		{
			free_tab(cmd_path);
			return (path);
		}
		free (path);
	}
	free_tab(cmd_path);
	return (cmd);
}
