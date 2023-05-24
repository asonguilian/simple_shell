#include "main.h"

/**
  * _isspace - checks if a string that ends with '\n' contains space only
  * @str: string
  * Return: 1 if string contains only spaces, 0 otherwise
  */

int _isspace(char *str)
{
	int space = 1;

	while (*str != '\n')
	{
		if (*str != ' ')
		{
			space = 0;
			break;
		}
		str++;
	}
	return (space);
}
