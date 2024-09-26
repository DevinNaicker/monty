#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long my_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *bufptr = NULL;
	char *p = NULL;
	size_t size;
	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	bufptr = *lineptr;
	size = *n;

	if (bufptr == NULL || size == 0)
	{
		size = 128;
		bufptr = malloc(size);
		if (bufptr == NULL)
			return (-1);
	}

	p = bufptr;
	while ((c = fgetc(stream)) != EOF)
	{
		if ((size_t)(p - bufptr) > (size - 1))
		{
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL)
				return (-1);
			p = bufptr + (p - *lineptr);
		}
		*p++ = (char)c;
		if (c == '\n')
			break;
	}

	*p = '\0';
	*lineptr = bufptr;
	*n = size;

	if (c == EOF && p == bufptr)
		return (-1);

	return ((long)(p - bufptr));
}
