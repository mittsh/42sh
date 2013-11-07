#include "mmalloc.h"

/**
** @brief               Moves a memory pointer.
** @param ptr           Input pointer.
** @param move          Input moving size.
** @return              Returns moving result.
*/
static inline void      *memory_move(void                       *ptr,
                                     size_t                     move)
{
  char                  *memory = ptr;

  return (memory + move);
}

/**
** @brief               Frees one block.
** @param mmalloc       Memory allocated.
** @param mem           Heap manager.
** @return              void
*/
static inline void      mfree_block(s_mmalloc                   *mmalloc,
                                    s_mmalloc_mem               *mem)
{
  if (mmalloc->prev == NULL)
    mem->first = mmalloc->next;
  else
    mmalloc->prev->next = mmalloc->next;

  if (mmalloc->next == NULL)
    mem->last = mmalloc->prev;
  else
    mmalloc->next->prev = mmalloc->prev;

  free(mmalloc);
}

int                     mfree(void                              *ptr)
{
  s_mmalloc_mem         *mem = NULL;
  s_mmalloc             *mmalloc = NULL;

  if (ptr == NULL)
    return (3);

  mem = g_shell->mmalloc;

  if (mem == NULL)
    return (2);

  mmalloc = memory_move(ptr, -(sizeof (s_mmalloc)));
  mfree_block(mmalloc, mem);

  return (1);
}
