#include "dynamic_string.h"

char                    *dynamic_string_getstr(s_dynamic_string *dynstr)
{
  if (dynstr == NULL)
    return (NULL);

  return (dynstr->str);
}
