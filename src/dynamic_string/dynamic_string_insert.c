#include "dynamic_string.h"

void                    dynamic_string_insert(s_dynamic_string  *dynstr,
                                              char              c,
                                              int               pos)
{
  int                   i = 0;

  if (dynstr == NULL || pos > dynstr->len)
    return;

  if (dynstr->len + 1 >= dynstr->max_len)
    dynamic_string_resize(dynstr);

  for (i = dynstr->len - 1; i >= pos; i--)
    dynstr->str[i + 1] = dynstr->str[i];

  dynstr->str[pos] = c;
  dynstr->str[dynstr->len + 1] = '\0';
  dynstr->len++;
}
