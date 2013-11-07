#include "masso.h"

void                    masso_freep(s_masso     *asso,
                                    void        (*cb)())
{
  int                   i = 0;

  if (asso != NULL && asso->array != NULL)
  {
    for (; i < asso->size; i++)
    {
      mfree(asso->array[i].key);
      cb(asso->array[i].value);
    }

    mfree(asso->array);
    mfree(asso);
  }
}
