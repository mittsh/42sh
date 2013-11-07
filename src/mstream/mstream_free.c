#include "mstream.h"

int                     mstream_close(void)
{
  s_mstream_mem         *mem = NULL;
  s_mstream             *mstream = NULL;
  s_mstream             *next = NULL;

  mem = g_shell->mstream;

  if (mem == NULL)
    return (2);

  for (mstream = mem->first; mstream != NULL; mstream = next)
  {
    next = mstream->next;

    if (mstream->type == MSTREAM_ST)
      fclose(mstream->f);
    if (mstream->type == MSTREAM_FD)
      close(mstream->filedes);

    mfree(mstream);
  }

  free(mem);

  return (1);
}
