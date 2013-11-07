#include "dynamic_string.h"

void                    dynamic_string_pushs(s_dynamic_string   *dynstr,
                                             char               *str)
{
  if (dynstr == NULL || str == NULL)
    return;

  for (; *str != '\0'; str++)
    dynamic_string_push(dynstr, *str);
}
