#include "main.h"

/**
 * handle_builtin - handle built-in commands
 * @args: pointer to array of command arguments
 * @env: pointer to array containing environment
 * @num_args: number of tokens in command
 * @cmd: command
 * Return: 1 if command is built-in command, otherwise 0
 */


int handle_builtin(char **args, char **env, int num_args, char *cmd)
{	int value;

	if (num_args <= 0)
		return (0);
	if (_strcmp(args[0], "exit") == 0)
	{
		if (num_args == 2)
		{
			if (_isinteger(args[1]) == 1)
			{
				value = _atoi(args[1]);
				free(args);
				free(cmd);
				exit_shell(value);
			}
			else
			{
				free(args);
				free(cmd);
				return (1);
			}
		}
		else if (num_args == 1)
		{
			free(args);
			free(cmd);
			exit_shell(EXIT_SUCCESS);
		}
		else
			return (0);
	}
	else if (num_args == 1 && _strcmp(args[0], "env") == 0)
	{
		free(args);
		free(cmd);
		print_env(env);
		return (1);
	}
	else
		return (0);
	return (1);
}
