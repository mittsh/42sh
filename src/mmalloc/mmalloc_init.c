#include "mmalloc.h"

int                     mmalloc_init(void)
{
  s_mmalloc_mem         *mem = NULL;

  if ((mem = malloc(sizeof (s_mmalloc_mem))) == NULL)
  {
    g_shell->mmalloc = NULL;
    return (2);
  }

  mem->first = NULL;
  mem->last = NULL;

  g_shell->mmalloc = mem;

  return (1);
}
