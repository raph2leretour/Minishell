/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/16 16:18:21 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*   INCLUDES                                                                 */
/******************************************************************************/
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/
/*
 * typedef struct s_env
 * {
 * 	bool			e;
 * 	char			*value;
 * 	struct s_env	*next;
 * }	t_env;
 */

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		execution(t_command *s_cmd);
int		create_pipe(t_commmand *s_cmd);
void	pwd(void);
void	cd(char *array);
void	ft_env(t_env *env);
void	echo(char **array);
void	clear_env(t_env *env);
void	unset(char *name, t_env *env);
void	ft_exit(char *strn, t_env *env);
void	ft_export(char *value, t_env *env);
void	ft_error(const char *s, int errnum);
t_env	*env_init(char **env);

#endif
