#include "mmalloc.h"

int                     mmalloc_free(void)
{
  s_mmalloc_mem         *mem = NULL;
  s_mmalloc             *mmalloc = NULL;
  s_mmalloc             *next = NULL;

  mem = g_shell->mmalloc;

  if (mem == NULL)
    return (2);

  for (mmalloc = mem->first; mmalloc != NULL; mmalloc = next)
  {
    next = mmalloc->next;
    free(mmalloc);
  }

  free(mem);

  return (1);
}
