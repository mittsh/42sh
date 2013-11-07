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
** @brief               Reallocs an allocated block.
** @param mmalloc       Allocated block.
** @param mem           Memory heap manager.
** @param size          New block size.
*/
static inline void      *mrealloc_block(s_mmalloc               *mmalloc,
                                        s_mmalloc_mem           *mem,
                                        int                     size)
{
  mmalloc = realloc(mmalloc, size + sizeof (s_mmalloc));

  if (mmalloc->prev == NULL)
    mem->first = mmalloc;
  else
    mmalloc->prev->next = mmalloc;

  if (mmalloc->next == NULL)
    mem->last = mmalloc;
  else
    mmalloc->next->prev = mmalloc;

  mmalloc->ptr = memory_move(mmalloc, sizeof (s_mmalloc));

  return (memory_move(mmalloc, sizeof (s_mmalloc)));
}

void                    *mrealloc(void                          *ptr,
                                  size_t                        size)
{
  s_mmalloc_mem         *mem = NULL;
  s_mmalloc             *block = NULL;

  if (ptr == NULL)
    return (mmalloc(size));

  mem = g_shell->mmalloc;

  if (mem == NULL)
    return (ptr);

  block = memory_move(ptr, -(sizeof (s_mmalloc)));
  ptr = mrealloc_block(block, mem, size);

  return (ptr);
}
