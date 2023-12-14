#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	char current = buf[j];
	char next = buf[j + 1];

	if ((current == '|' && next == '|') || (current == '&' && next == '&') || current == ';')
	{
		buf[j] = 0;
		j += (current == ';' ? 0 : 1);
		info->cmd_buf_type = (current == '|') ? CMD_OR : (current == '&') ? CMD_AND : CMD_CHAIN;
		*p = j;
		return (1);
	}
	return (0);
}

/**
 * check_chain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status) || (info->cmd_buf_type == CMD_OR && !info->status))
	{
		buf[i] = 0;
		j = len;
	}
	*p = j;
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (*old != NULL);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;

	while (info->argv[i])
	{
		if (info->argv[i][0] == '$' && info->argv[i][1])
		{
			if (!_strcmp(info->argv[i], "$?"))
				replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
			else if (!_strcmp(info->argv[i], "$$"))
				replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			else
			{
				list_t *node = node_starts_with(info->env, &info->argv[i][1], '=');
				replace_string(&(info->argv[i]), (node) ? _strdup(_strchr(node->str, '=') + 1) : _strdup(""));
			}
		}
		i++;
	}
	return (1);
}
