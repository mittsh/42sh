#include "dynamic_string.h"

void                    dynamic_string_renew(s_dynamic_string   *dynstr)
{
  if (dynstr == NULL)
    return;

  mfree(dynstr->str);
  dynstr->len = 0;
  dynstr->max_len = 2;
  dynstr->str = mmalloc(dynstr->max_len);
  dynstr->str[0] = '\0';
}
