#include <stdio.h>
#include "masso.h"

/**
** @brief               Gets a data from array.
** @param asso          Input associative array.
** @param key           Input key.
** @return              Returns offset.
*/
static inline int       masso_get_data(s_masso                  *asso,
                                       char                     *key)
{
  s_masso_data          *array = NULL;
  int                   i = 0;

  array = asso->array;

  for (; i < asso->size; i++)
  {
    if (mstring_compare(key, array->key))
      return (i);
    array++;
  }

  return (-1);
}

int                     masso_set(s_masso                       *asso,
                                  char                          *key,
                                  void                          *value)
{
  int                   pos = (-1);
  s_masso_data          *data = NULL;

  pos = masso_get_data(asso, key);

  if (pos == (-1))
    return (masso_add(asso, key, value));

  data = asso->array + pos;

  mfree(data->value);

  data->value = value;

  return (pos);
}
