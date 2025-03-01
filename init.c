/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:40:58 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/13 12:05:22 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc)
{
	if (argc != 5)
	{
		perror("\e[31mThe program should be executed as follows:\n"
			"\t./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
}

int	find_path_var(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

char	*check_commands(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*file_path;
	char	*tmp;

	if ((access(cmd, X_OK) == 0 && ft_strchr(cmd, '/') != NULL) || cmd == NULL)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') != NULL && access(cmd, X_OK) != 0)
		return (perror(cmd), NULL);
	if (find_path_var(env) == -1)
		return (perror(cmd), NULL);
	paths = ft_split(env[find_path_var(env)] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		file_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(file_path, X_OK) == 0)
			return (free_dbl_ptr(paths, i + 1), file_path);
		free(file_path);
		i++;
	}
	return (free(paths), perror(cmd), NULL);
}

void	close_all(int fd, int pfd[2])
{
	close(fd);
	close(pfd[0]);
	close(pfd[1]);
}
