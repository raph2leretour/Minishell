/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2023/12/20 15:31:02 by rtissera         ###   ########.fr       */
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
# include "lexer.h"
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		is_builtin(char *path);
int		create_pipe(t_command *s_cmd);
int		execution(t_command *s_cmd, t_simple_cmd *cmd);
char	**split_cmd(t_simple_cmd *cmd);
void	pwd(void);
void	cd(char *array);
void	ft_env(t_simple_cmd *cmd, t_env *env);
void	echo(char **array);
void	clear_env(t_env *env);
void	ft_exec(t_command *t_cmd);
void	clear_pipes(t_command *s_cmd);
void	unset(char *name, t_env *env);
void	ft_exit(char *strn, t_env *env);
void	ft_export(char *value, t_env *env);
void	ft_error(const char *s, int errnum);
void	do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token);
t_env	*env_init(char **env);

#endif
