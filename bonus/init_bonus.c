/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:40:58 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/09 10:16:52 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_files(int argc, char **argv, int fds[2])
{
	check_argc(argc);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (argc < 6)
			return (perror("\e[31mThe program should be executed as follows:\n"
					"\t./pipex_bonus here_doc LIMITER cmd cmd1 file\n"), exit(1));
		if (access(argv[argc - 1], F_OK) == 0
			&& access(argv[argc - 1], W_OK) == -1)
			return (perror(argv[argc - 1]), exit(1));
		fds[0] = dup(0);
		fds[1] = 0;
		return ;
	}
	if (argc < 5)
	{
		perror("\e[31mThe program should be executed as follows:\n"
			"\t./pipex file1 cmd1 cmd2 file2\n");
		exit(1);
	}
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) == -1)
		return (perror(argv[argc - 1]), exit(1));
	if (access(argv[1], R_OK) == -1)
		return (perror(argv[1]), exit(1));
	fds[0] = open(argv[1], O_RDONLY);
	fds[1] = 1;
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

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') != NULL)
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

void	allocate(char ****cmds_args, char is_here, int argc, char **argv)
{
	int	i;

	i = 0;
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		*cmds_args = malloc(((argc - 4) + 1) * sizeof(char **));
		while (i < argc - 4)
		{
			(*cmds_args)[i] = argv;
			i++;
		}
		(*cmds_args)[argc - 4] = NULL;
	}
	else
	{
		*cmds_args = malloc(((argc - 3) + 1) * sizeof(char **));
		while (i < argc - 3)
		{
			(*cmds_args)[i] = argv;
			i++;
		}
		(*cmds_args)[argc - 3] = NULL;
	}
}

int	cmds_number(char ***cmds_args)
{
	int	i;

	i = 0;
	while (cmds_args[i])
		i++;
	return (i);
}
