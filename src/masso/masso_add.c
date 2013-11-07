#include "masso.h"

/**
** @brief               Reallocs assocative array.
** @param asso          Input associative array.
** @param max_size      New maximum size.
** @return              void
*/
static void             masso_realloc(s_masso   *asso,
                                      int       max_size)
{
  s_masso_data          *new_array;
  s_masso_data          *new_array_ref;
  s_masso_data          *old_array;
  int                   i = 0;

  if ((new_array = mmalloc(max_size * sizeof (s_masso_data))) != NULL)
  {
    new_array_ref = new_array;
    old_array = asso->array;
    for (; i < asso->size && i < max_size; i++)
    {
      *new_array = *old_array;
      new_array++;
      old_array++;
    }
    mfree(asso->array);
    asso->array = new_array_ref;
    asso->max_size = max_size;
  }
}

int                     masso_add(s_masso       *asso,
                                  char          *key,
                                  void          *value)
{
  int                   pos = 0;

  if (asso->size == asso->max_size)
    masso_realloc(asso, asso->max_size * 2);

  pos = asso->size;

  asso->array[pos].key = mstring_copy(key);
  asso->array[pos].value = value;

  asso->size++;

  return (pos);
}

