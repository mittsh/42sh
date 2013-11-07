#include "masso.h"

void                    *masso_getn(s_masso     *asso,
                                    int         n)
{
  if (asso == NULL || n >= asso->size)
    return (NULL);

  return (asso->array[n].value);
}
