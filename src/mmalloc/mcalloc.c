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

void                    *mcalloc(size_t                         count,
                                 size_t                         size)
{
  void                  *ptr = NULL;
  s_mmalloc             *new = NULL;

  if ((new = calloc((size * count) + sizeof (s_mmalloc), 1)) == NULL)
    return (NULL);

  ptr = memory_move(new, sizeof (s_mmalloc));

  new->ptr = ptr;
  new->next = NULL;

  if (g_shell->mmalloc->first == NULL)
  {
    g_shell->mmalloc->first = new;
    g_shell->mmalloc->last = new;
    new->next = NULL;
    new->prev = NULL;
  }
  else
  {
    new->prev = g_shell->mmalloc->last;
    g_shell->mmalloc->last->next = new;
    g_shell->mmalloc->last = new;
  }

  return (ptr);
}
