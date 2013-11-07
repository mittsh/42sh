#include "masso.h"

s_masso                 *masso_init(void)
{
  s_masso               *asso = NULL;

  if ((asso = mmalloc(sizeof (s_masso))) == NULL)
    return (NULL);

  asso->size = 0;
  asso->max_size = MASSO_DEFAULT_SIZE;

  if ((asso->array = mmalloc(asso->max_size * sizeof (s_masso_data))) == NULL)
  {
    mfree(asso);
    return (NULL);
  }

  return (asso);
}
