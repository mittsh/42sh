#include "mmalloc.h"

/**
** @brief               Gets a memory mointer.
** @param ptr           Input memory adress.
** @return              Returns its pointer.
*/
static inline void      *get_ptr(void                           *ptr)
{
  return (ptr);
}

/**
** @brief               Calculates difference between two pointers.
** @param ptr1          First pointer.
** @param ptr2          Second pointer.
** @return              Returns difference.
*/
static inline int       get_diff(void                           *ptr1,
                                 void                           *ptr2)
{
  char                  *p1 = ptr1;
  char                  *p2 = ptr2;

  return (p2 - p1);
}

int                     mmalloc_debug(void)
{
  s_mmalloc_mem         *mem = NULL;
  s_mmalloc             *mmalloc = NULL;

  mem = g_shell->mmalloc;

  if (mem == NULL)
    return (2);

  printf("***************\nMMALLOC MEMORY MANAGER\n***************\n");

  printf("First : %p. Last : %p\n", get_ptr(mem->first), get_ptr(mem->last));

  for (mmalloc = mem->first; mmalloc != NULL; mmalloc = mmalloc->next)
  {
    printf("Allocation of %p by manager %p (diff : %d).",
           get_ptr(mmalloc->ptr), get_ptr(mmalloc),
           get_diff(mmalloc, mmalloc->ptr));

    printf("Next : %p. Previous : %p.\n",
           get_ptr(mmalloc->next), get_ptr(mmalloc->prev));
  }

  return (1);
}
