/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:40:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/10 11:48:29 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	epilogue(int fds[2], int pfd[2], char ***cmds_args)
{
	int	i;

	i = 0;
	close(fds[0]);
	close(fds[1]);
	close(pfd[0]);
	close(pfd[1]);
	while (cmds_args[i] != NULL)
	{
		free_dbl_ptr(cmds_args[i], 0);
		i++;
	}
	free(cmds_args);
}

int	check(int nth, char **argv, char **env, char ***cmds_args)
{
	char	**tmp;
	char	*tmp1;
	int		offset;

	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		offset = 3;
	else
		offset = 2;
	if (valid_quotes(argv[offset + nth]) == 0)
		return (cmds_args[nth] = NULL,
			remove_element(cmds_args, nth), perror("Invalid quotes"), 0);
	cmds_args[nth] = ft_split(argv[nth + offset], ' ');
	if (cmds_args[nth][0] == NULL)
		return (perror("' ' is not a command"), 0);
	tmp = cmds_args[nth];
	tmp1 = cmds_args[nth][0];
	cmds_args[nth][0] = check_commands(env, cmds_args[nth][0]);
	if (cmds_args[nth][0] == NULL)
	{
		tmp[0] = tmp1;
		return (free_dbl_ptr(tmp, 0), cmds_args[nth] = NULL,
			remove_element(cmds_args, nth), 0);
	}
	return (free(tmp1), 1);
}

void	execute2(int fds[2], int pfd[2], char ***cmds_args, int nth)
{
	int		pfd2[2];

	pfd2[0] = pfd[0];
	pfd2[1] = pfd[1];
	close(pfd[1]);
	pipe(pfd);
	if (fork() == 0)
	{
		dup2(pfd2[0], 0);
		dup2(pfd[1], 1);
		close(pfd2[0]);
		close_all(fds, pfd);
		execve(cmds_args[nth][0], cmds_args[nth], NULL);
		epilogue(fds, pfd, cmds_args);
		exit(1);
	}
	close(pfd2[0]);
}

void	execute(int fds[2], int pfd[2], char ***cmds_args, int nth)
{
	if (nth == 0)
	{
		if (fork() == 0)
		{
			dup2(fds[0], 0);
			dup2(pfd[1], 1);
			close_all(fds, pfd);
			execve(cmds_args[0][0], cmds_args[0], NULL);
			return (epilogue(fds, pfd, cmds_args), exit(1));
		}
	}
	else if (nth == cmds_number(cmds_args) - 1)
	{
		close(pfd[1]);
		if (fork() == 0)
		{
			dup2(pfd[0], 0);
			dup2(fds[1], 1);
			close_all(fds, pfd);
			close(fds[1]);
			execve(cmds_args[nth][0], cmds_args[nth], NULL);
			return (epilogue(fds, pfd, cmds_args), exit(1));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fds[2];
	char	***cmds_args;
	int		pfd[2];
	int		i;

	i = 1;
	check_files(argc, argv, fds);
	allocate(&cmds_args, ft_strncmp("here_doc", argv[1], 8), argc, argv);
	pipe(pfd);
	if (ft_strncmp("here_doc", argv[1], 8) == 0
		&& check(0, argv, env, cmds_args) != 0)
		execute3(fds, pfd, cmds_args, argv);
	else if (ft_strncmp("here_doc", argv[1], 8) != 0
		&& check(0, argv, env, cmds_args) != 0)
		execute(fds, pfd, cmds_args, 0);
	while (i < cmds_number(cmds_args) - 1)
	{
		if (check(i, argv, env, cmds_args) != 0)
			execute2(fds, pfd, cmds_args, i);
		i++;
	}
	creating_outfile(fds, argv, argc);
	if (check(i, argv, env, cmds_args) != 0)
		execute(fds, pfd, cmds_args, i);
	return (wait_for_all(), epilogue(fds, pfd, cmds_args), 0);
}
