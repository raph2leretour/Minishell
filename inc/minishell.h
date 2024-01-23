/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2024/01/23 20:31:45 by rtissera         ###   ########.fr       */
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
# include <signal.h>
# include "lexer.h"
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		pwd(void);
int		ft_env(t_env *env);
int		is_pipe(t_command *cmd);
int		create_pipe(t_command *s_cmd);
int		echo(char **array, t_env *env);
int		dupificator(t_simple_cmd *cmd);
int		unset(t_env *env, t_token *token);
int		is_any_redirection(t_simple_cmd *cmd);
int		ft_export(t_command *s_cmd, t_token *token);
int		execution(t_command *s_cmd, t_simple_cmd *cmd);
int		cd(t_command *cmd, t_token *token, t_env *env);
int		do_builtin(t_command *t_cmd, t_simple_cmd *cmd, t_token *token, int b);
char	**freeror(char **s_cmd);
char	*get_key(char *env_var);
char	*get_value(char *env_var);
char	**get_true_env(t_env *s_env);
char	*ft_getenv(char *s, t_env *env);
char	**split_cmd(t_simple_cmd *cmd, bool skip);
void	free_env(t_env *env);
void	free_array(char **a);
void	ft_wait(pid_t last_pid);
void	ft_karl(t_token *token);
void	ft_exec(t_command *t_cmd);
void	close_fds(t_simple_cmd *cmd);
void	ft_error(char *s, int errnum);
void	clear_pipes(t_command *s_cmd);
void	redirect_end(t_simple_cmd *cmd);
void	set_oldpwd(t_env *env, char *oldpwd);
void	ft_exit(t_command *cmd, t_token *token);
void	do_exec(t_command *t_cmd, t_simple_cmd *t_scmd, t_env *s_env);
void	cd_arg(t_env *env, char *path, char *oldpwd);
void	ft_reset(t_env *env, char *key, char *value);
void	child_process(t_command *t_cmd, t_simple_cmd *cmd);
t_env	*init_env_var(char *key, char *value);

#endif
