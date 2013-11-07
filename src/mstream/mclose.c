#include "mstream.h"

static inline void      mfree_block(s_mstream                   *mstream,
                                    s_mstream_mem               *mem)
{
  if (mstream->prev == NULL)
    mem->first = mstream->next;
  else
    mstream->prev->next = mstream->next;

  if (mstream->next == NULL)
    mem->last = mstream->prev;
  else
    mstream->next->prev = mstream->prev;

  mfree(mstream);
}

int                     mfclose(FILE                            *f)
{
  s_mstream_mem         *mem = NULL;
  s_mstream             *mstream = NULL;
  int                   res = 1;

  mem = g_shell->mstream;

  if (mem == NULL)
    return (2);

  for (mstream = mem->first; mstream != NULL; mstream = mstream->next)
    if (mstream->type == MSTREAM_ST && mstream->f == f)
    {
      res = fclose(f);
      mfree_block(mstream, mem);
      return (res);
    }

  fprintf(stderr, "Warning ! Cannot find stream to close. Close anyway.\n");

  res = fclose(f);

  return (res);
}

int                     mclose(int                              filedes)
{
  s_mstream_mem         *mem = NULL;
  s_mstream             *mstream = NULL;
  int                   res = 1;

  mem = g_shell->mstream;

  if (mem == NULL)
    return (2);

  for (mstream = mem->first; mstream != NULL; mstream = mstream->next)
    if (mstream->type == MSTREAM_FD && mstream->filedes == filedes)
    {
      res = close(filedes);
      mfree_block(mstream, mem);
      return (1);
    }

  fprintf(stderr, "Warning ! Cannot find filedes to close. Close anyway.\n");

  res = close(filedes);

  return (res);
}
