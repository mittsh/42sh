#include "vars.h"

char                    **vars_expand_all(char                  *str[],
                                          int                   *error)
{
  char                  **tmp = str;
  int                   size = 0;
  char                  **res = NULL;
  int                   mode = 0;

  for (tmp = str; *tmp != NULL; tmp++)
    size++;

  res = mmalloc(sizeof (size_t) * (size + 1));

  for (tmp = res; *str != NULL; str++)
  {
    *tmp = *str;
    *tmp = vars_expand_quotes(*tmp, &mode);
    if (mode == 0)
      *tmp = vars_expand_tilde(*tmp);
    if (mode != 2)
    {
      *tmp = vars_expand(*tmp);
      *tmp = vars_expand_arithmetic(*tmp, error);
      if (ERROR_EVALEXPR == *error)
        return (NULL);
    }
    tmp++;
  }

  *tmp = NULL;
  *error = ERROR_NONE;
  return (res);
}
