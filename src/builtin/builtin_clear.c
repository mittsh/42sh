#include "builtin.h"

int                     builtin_clear(s_builtin_fd              *builtin_fd)
{
	fprintf(builtin_fd->fout, "%c[H%c[J", 27, 27);
	fflush(NULL);

	return (0);
}

