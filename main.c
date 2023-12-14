#include "shell.h"

/**
 * handle_open_error - handles errors during the open system call
 * @program: name of the program
 * @filename: name of the file
 *
 * This function handles errors during the open system call. It checks the
 * value of errno and exits with an appropriate status code.
 *
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
void handle_open_error(char *program, char *filename);

int main(int ac, char **av)
{
info_t info[] = {INFO_INIT};
int fd = 2;

/* Increment fd by 3 */
fd += 3;

asm("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fd)
: "r" (fd));

if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
handle_open_error(av[0], av[1]);
}
else
{
info->readfd = fd;
}
}

populate_env_list(info);
read_history(info);
hsh(info, av);

return (EXIT_SUCCESS);
}

/**
 * handle_open_error - handles errors during the open system call
 * @program: name of the program
 * @filename: name of the file
 *
 * This function handles errors during the open system call. It checks the
 * value of errno and exits with an appropriate status code.
 */
void handle_open_error(char *program, char *filename)
{
if (errno == EACCES)
{
exit(126);
}
else if (errno == ENOENT)
{
_eputs(program);
_eputs(": 0: Can't open ");
_eputs(filename);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
else
{
perror(program);
exit(EXIT_FAILURE);
}
}
