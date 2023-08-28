#include "monty.h"


/**
 * main - monty execution starts
 * Author - Abdulkareem Olumoh
 * @argc: arg counter
 * @argv: arg vector
 *
 * Return: 0 on success
 */


int main(int argc, char *argv[])
{
	FILE *file_ptr;
	size_t count;
	ssize_t line_read;
	char *upcode = NULL, *arg = NULL, *buffer = NULL;
	unsigned int line_num = 0, num = 0;
	stack_t *buff = NULL;
	void (*up_code_handler)(stack_t **stack, unsigned int arg);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file_ptr = fopen(argv[1], "r");
	if (file_ptr == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((line_read = getline(&buffer, &count, file_ptr)) != -1)
	{
		line_num += 1;
		buffer[line_read - 1] = '\0';
		upcode = strtok(buffer, " ");
		arg = strtok(NULL, " ");
		if (upcode == NULL)
			continue;
		if (strcmp(upcode, "#") == 0)
			continue;
		if (strcmp(upcode, "push") == 0)
		{
			if (if_num(arg) == 0)
			{
				fprintf(stderr, "L%d: usage: push integer", line_num);
				exit(EXIT_FAILURE);
			}
			num = atoi(arg);
			fun_push(&buff, num);
			continue;
		}
		up_code_handler = select_opcode_handler(upcode);
		if (up_code_handler)
			up_code_handler(&buff, line_num);
		else
		{
			free_stack(&buff);
			fprintf(stderr, "L%d: unknown instruction %s\n", line_num, upcode);
			exit(EXIT_FAILURE);
		}
	}
	free_stack(&buff);
	fclose(file_ptr);
return (0);
}
