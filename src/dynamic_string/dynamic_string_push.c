#include "dynamic_string.h"

void                    dynamic_string_push(s_dynamic_string    *dynstr,
                                            char                c)
{
  if (dynstr == NULL)
    return;

  if (dynstr->len + 1 == dynstr->max_len)
    dynamic_string_resize(dynstr);

  dynstr->str[dynstr->len] = c;
  dynstr->str[dynstr->len + 1] = '\0';
  dynstr->len++;
}
