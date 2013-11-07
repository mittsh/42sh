#include "dynamic_string.h"

void                    dynamic_string_resize(s_dynamic_string  *dynstr)
{
  if (dynstr == NULL)
    return;

  dynstr->max_len *= 2;
  dynstr->str = mrealloc(dynstr->str, dynstr->max_len);
}
