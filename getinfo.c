#include "shell.h"

/* Other function declarations */
void execute_command(info_t *info);

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
int i;

info->fname = av[0];
info->argv = NULL;
info->path = NULL;
info->argc = 0;

if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}

if (info->argv)
{
for (i = 0; info->argv[i]; i++)
;
info->argc = i;

replace_alias(info);
replace_vars(info);
}
}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;
if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}

/**
 * execute_command - Placeholder for command execution logic
 * @info: Parameter struct
 */
void execute_command(info_t *info)
{
/* Your command execution logic goes here */
/* For example, print the arguments */
int i;
for (i = 0; i < info->argc; i++)
{
printf("Argument %d: %s\n", i + 1, info->argv[i]);
}
}

int main(void)
{
info_t info;

/* Example usage */
char *input = "ls -l -a";
clear_info(&info);
info.arg = input;
set_info(&info, NULL);

/* Execute the command */
execute_command(&info);

/* Free allocated memory */
free_info(&info, 1);

return (0);
}
