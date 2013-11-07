#include "dynamic_string.h"

void                    dynamic_string_pop(s_dynamic_string     *dynstr)
{
  if (dynstr == NULL)
    return;

  if (dynstr->len > 0)
  {
    dynstr->len--;
    dynstr->str[dynstr->len + 1] = '\0';
  }
}
