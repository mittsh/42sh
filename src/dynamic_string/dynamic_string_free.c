#include "dynamic_string.h"

void                    dynamic_string_free(s_dynamic_string    *dynstr)
{
  if (dynstr == NULL)
    return;

  mfree(dynstr->str);
  mfree(dynstr);
}
