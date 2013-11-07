#include "mstream.h"

int                     mstream_init(void)
{
  s_mstream_mem         *mem = NULL;

  if ((mem = malloc(sizeof (s_mstream_mem))) == NULL)
  {
    g_shell->mstream = NULL;
    return (2);
  }

  mem->first = NULL;
  mem->last = NULL;

  g_shell->mstream = mem;

  return (1);
}
