/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilosav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:57:10 by smilosav          #+#    #+#             */
/*   Updated: 2023/11/02 22:49:07 by smilosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

#include "../libft/include/libft.h"

typedef enum s_token_type
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
}				t_token_type;

typedef struct			s_token
{
	char		*str;
	t_token_type		type;
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
t_token	*token_last(t_token *lst);
void	add_token(t_token **lst, t_token *new_token);
#endif
