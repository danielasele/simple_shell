#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

return (S_ISREG(st.st_mode) != 0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
int len = stop - start;
char *buf = malloc(len + 1);

if (buf == NULL)
return (NULL);

_strncpy(buf, pathstr + start, len);
buf[len] = '\0';

return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int curr_pos = 0;
char *path = NULL;

if (!pathstr)
return (NULL);

if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
{
return (is_cmd(info, cmd) ? cmd : NULL);
}

for (int i = 0; pathstr[i]; i++)
{
if (pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
_strcat(path, "/");
_strcat(path, cmd);

if (is_cmd(info, path))
return (path);

curr_pos = i + 1;
}
}

/* Check the last part of the PATH */
path = dup_chars(pathstr, curr_pos, _strlen(pathstr));
_strcat(path, "/");
_strcat(path, cmd);
return (is_cmd(info, path) ? path : NULL);
}
