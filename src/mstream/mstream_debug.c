#include "mstream.h"

static inline void      *get_ptr(void                           *ptr)
{
  return (ptr);
}

int                     mstream_debug(void)
{
  s_mstream_mem         *mem = NULL;
  s_mstream             *mstream = NULL;

  mem = g_shell->mstream;

  if (mem == NULL)
    return (2);

  printf("***************\nMSTREAM : STREAM AND FILE DESCRIPTOR MANAGER");
  printf("\n***************\n");

  printf("First : %p. Last : %p\n", get_ptr(mem->first), get_ptr(mem->last));

  for (mstream = mem->first; mstream != NULL; mstream = mstream->next)
  {
    if (mstream->type == MSTREAM_ST)
      printf("Open stream %p by manager %p. Next : %p. Previous : %p.\n",
             get_ptr(mstream->f), get_ptr(mstream),
             get_ptr(mstream->next), get_ptr(mstream->prev));
    if (mstream->type == MSTREAM_FD)
      printf("Open filedes %d by manager %p. Next : %p. Previous : %p.\n",
             mstream->filedes, get_ptr(mstream),
             get_ptr(mstream->next), get_ptr(mstream->prev));
  }

  return (1);
}
