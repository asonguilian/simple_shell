#include "main.h"

/**
 * handle_interactive_mode - handles the interactive mode of the shell
 * @prompt: the prompt to display
 * @env: pointer to array containing the environment
 * @file_name: executable file name
 * Return: void
 */
void handle_interactive_mode(char *prompt, char **env, char *file_name)
{
	char *command = NULL, **args;
	int cmd_val, num_args, flag_builtin;

	while (1)
	{
		print_msg(prompt);
		fflush(stdout);
		cmd_val = read_cmd(&command);
		if (cmd_val == 1)
		{
			free(command);
			continue;
		}
		if (cmd_val == 2 || cmd_val == 3)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		args = malloc(sizeof(char *) * 1024);
		if (args == NULL)
		{
			free(command);
			perror(file_name);
			exit(EXIT_FAILURE);
		}
		num_args = parse_cmd(command, args);
		if (num_args == 0)
		{
			free(command);
			free(args);
			return;
		}
		flag_builtin = handle_builtin(args, env, num_args, command);
		if (flag_builtin == 1)
			continue;
		execute_cmd(&args, file_name, env);
		free(command);
		free(args);
	}
}

/**
 * handle_non_interactive_mode - handles the non-interactive mode of the shell
 * @env: pointer to array containing the environment
 * @file_name: executable file name
 * Return: void
 */
void handle_non_interactive_mode(char **env, char *file_name)
{
	char *command = NULL;
	int cmd_val, num_args, flag_builtin;
	char **args;

	cmd_val = read_cmd(&command);
	if (cmd_val == 1 || cmd_val == 2 || cmd_val == 3)
	{
		free(command);
		exit(EXIT_SUCCESS);
	}
	args = malloc(sizeof(char *) * 1024);
	if (args == NULL)
	{
		free(command);
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	num_args = parse_cmd(command, args);
	if (num_args == 0)
	{
		free(command);
		free(args);
		return;
	}
	flag_builtin = handle_builtin(args, env, num_args, command);
	if (flag_builtin == 1)
	{
		return;
	}
	execute_cmd(&args, file_name, env);
	free(command);
	free(args);
}

/**
 * main - super simple shell
 * @ac: number of argument
 * @argv: pointer to array containing arguments
 * @env: pointer to array containing the environment
 * Return: Always 0.
 */
int main(int ac, char *argv[], char **env)
{
	(void)ac;

	if (isatty(STDIN_FILENO))/*interactive mode*/
	{
		handle_interactive_mode("#cisfun$ ", env, argv[0]);
	}
	else /*non-interactive mode*/
	{
		handle_non_interactive_mode(env, argv[0]);
	}

	return (0);
}
