#include "dynamic_string.h"

void                    dynamic_string_remove(s_dynamic_string  *dynstr,
                                              int               pos)
{
  int                   i = 0;

  if (pos > dynstr->len - 1 || pos < 0)
    return;

  for (i = pos; i < dynstr->len - 1; i++)
    dynstr->str[i] = dynstr->str[i + 1];

  dynstr->str[i] = '\0';
  dynstr->len--;
}
