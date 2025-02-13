/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:41:10 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/13 12:01:18 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft.h"

void	check_args(int argc);
int		find_path_var(char **env);
char	*check_commands(char **env, char *cmd);
void	free_dbl_ptr(char **ptr, int i);
int		valid_quotes(char	*str);
void	free_trpl_ptr(char ***ptr, int i);
void	close_all(int fd, int pfd[2]);
int		open_input_file(char *filename, char **cmds_args[2], int pfd[2]);
void	epilogue(char **cmds_args[2]);
int		open_output_file(char *filename, char **cmds_args[2], int pfd[2]);
#endif
