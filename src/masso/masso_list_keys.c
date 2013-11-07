#include "masso.h"

void                    masso_list_keys(s_masso *asso,
                                        void    (*printer)())
{
  int                   i = 0;

  for (; i < asso->size; i++)
  {
    printer(masso_getn_key(asso, i));
    printer("\n");
  }
}
