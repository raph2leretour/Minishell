#include "minishell.h"
#include "lexer.h"


// execute command one by one
int execution(t_command *cmd)
{
	t_simple_cmd	*curr_cmd;
	t_pid pid;

	curr_cmd = cmd->first_cmd;
	while (curr_cmd)
	{
		// first create one fork per cmd
		pid = fork();
		// do nothing if you're not in the good process
		if (pid == 0)
			;
		// if you're in, gg
		else if (pid != 0)
		{
			dup2(STDIN, curr_cmd->infile);
			dup2(STDOUT, curr_cmd->outfile);
			// if there's not an absolute path = it's probably a builtin
			if (curr_cmd->full_path == NULL)
			{
				// test every builtin
				if (curr->full_cmd[0] == "echo")
					echo(curr_cmd);
				else if (curr->full_cmd[0] == "env")
					env(curr_cmd);
				. . .
				// if it's none of the builtins = error message
				else
					printf("message d'erreur\n");
			}
			// if it's not a builtin exec it
			execve(curr_cmd->full_path, curr_cmd->full_cmd, );
			// exec quit program so it's an error if you're still here
			return (-1);
		}
		curr_cmd = curr_cmd->next;
	}
	return 0;
}

// first of all: create all the pipes you need
int	create_pipe(t_command *cmd)
{
	int pip[2];

	while (cmd)
	{
		// create one pipe per cmd
		if (cmd->next != NULL)
		{
			if (pipe(pip))
			{
				cmd->out = pip[1];
				cmd->next->in = pip[0];
			}
		}
		cmd->next;
	}

}

/*
 regarder si le parsing fait le infile et le outfile dans le parsing
 full path n'est pas bon
*/
