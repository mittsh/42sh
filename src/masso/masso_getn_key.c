#include "masso.h"

char                    *masso_getn_key(s_masso *asso,
                                        int     n)
{
  if (asso == NULL || n >= asso->size)
    return (NULL);

  return (asso->array[n].key);
}
