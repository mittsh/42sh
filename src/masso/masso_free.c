#include "masso.h"

void                    masso_free(s_masso      *asso)
{
  int                   i = 0;

  if (asso != NULL && asso->array != NULL)
  {
    for (; i < asso->size; i++)
    {
      mfree(asso->array[i].key);
    }

    mfree(asso->array);
    mfree(asso);
  }
}
