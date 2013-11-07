#include "dynamic_string.h"

s_dynamic_string        *dynamic_string_init(void)
{
  s_dynamic_string      *dynstr = NULL;

  if ((dynstr = mmalloc(sizeof (s_dynamic_string))) == NULL)
    return (NULL);

  dynstr->len = 0;
  dynstr->max_len = 2;
  dynstr->str = mmalloc(dynstr->max_len);
  dynstr->str[0] = '\0';

  return (dynstr);
}
