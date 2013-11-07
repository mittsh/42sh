#include "masso.h"

void                    *masso_get(s_masso      *asso,
                                   char         *key)
{
  s_masso_data          *array;
  int                   i = 0;

  array = asso->array;

  for (; i < asso->size; i++)
  {
    if (mstring_compare(key, array->key))
      return (array->value);
    array++;
  }

  return (NULL);
}
