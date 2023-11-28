/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:30:06 by rtissera          #+#    #+#             */
/*   Updated: 2023/11/28 18:28:41 by rtissera         ###   ########.fr       */
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
# include "../libft/include/libft.h"

/******************************************************************************/
/*   STRUCTURES                                                               */
/******************************************************************************/
typedef struct s_env
{
	bool			e;
	char			*value;
	char			*name;
	struct s_env	*next;
}	t_env;

/******************************************************************************/
/*   FUNCTIONS                                                                */
/******************************************************************************/
int		ft_exit(char *strn, t_env *env);
void	pwd(void);
void	cd(char *array);
void	unset(char *name);
void	ft_env(t_env *env);
void	echo(char **array);
void	clear_env(t_env *env);
void	ft_export(char *value, t_env *env);
void	ft_error(const char *s, int errnum);
t_env	*env_init(char **env);

#endif
