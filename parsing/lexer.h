/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2023/12/05 18:44:17 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

#include "../libft/include/libft.h"
# define WORD 1
# define REDIRECTION 2
# define PARENTHESIS 3
# define PIPE 4
# define AND 5
# define SEMI 6

/*typedef enum s_token_type
{
	NO_TYPE,
	EMPTY,
	ARG,
	BUILTIN,
	INPUT, //<
	OUTPUT, //>
	APPEND, //>>
	HERE_DOC, //<<
	PIPE,
}				t_token_type;*/

typedef struct			s_token
{
	char		*str;
	int		type;
	//bool		expanded;
	struct s_token		*prev;
	struct s_token		*next;
}				t_token;

typedef	struct				s_command
{
	char			*string;
	//char			**envp;
	//char			**argv;
	struct s_token			*first_token;
}					t_command;

t_command *tokenize(char *command);

t_token	*init_token(char *value, int type);
t_token	*token_last(t_token *lst);

void	add_token(t_token **lst, t_token *new_token);
void	free_cmd(t_command *cmd);

int	add_token_word(t_command *cmd_struct, int i);
int	add_token_redirection(t_command *cmd_struct, int i);
int	add_token_parenthesis(t_command *cmd_struct, int i);
int	add_token_pipe(t_command *cmd_struct, int i);
int	add_token_and(t_command *cmd_struct, int i);
int	add_token_semi(t_command *cmd_struct, int i);
int	is_space(char c);
int	is_parenthesis(char c);
int	is_redirection(char c);
int	is_word(char c);

#endif
