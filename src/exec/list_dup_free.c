#include "exec.h"

void                    list_dup_free(s_list_dup                *list_dup)
{
  s_list_dup            *next = NULL;

  while (list_dup != NULL)
  {
    next = list_dup->next;
    mfree(list_dup);
    list_dup = next;
  }
}
